#include "XFileServerTask.h"
#include "XTools.h"
#include <iostream>
#include <string>
using namespace std;

string XFileServerTask::cur_dir_ = "./";
mutex XFileServerTask::cur_dir_mux_;

bool XFileServerTask::ReadCB (const XMsg * msg) {
    switch (msg->type) {
    case MSG_GETDIR:
        cout << "Deal MSG_GETDIR" << endl;
        GetDir (msg);
        break;
    case MSG_UPLOAD_INFO:
        cout << "Deal MSG_UPLOAD_INFO" << endl;
        Upload (msg);
        break;
    case MSG_DOWNLOAD_INFO:
        cout<<"Deal MSG_DOWNLOAD_INFO" << endl;
        Download (msg);
        break;
    case MSG_DOWNLOAD_COMPLETE:
        cout<<"Deal MSG_DOWNLOAD_COMPLETE" << endl;
        // 清理网络资源
        Close ();
        return false;
        break;
    default:
        break;
    }
    return true;
}

void XFileServerTask::Download (const XMsg * msg) {
    if (!msg->data || !msg ||msg->size <= 0)
        return;
    //1 打开文件
    filepath_ = msg->data;
    if (filepath_.empty ())
        return;
    ifs_.open (filepath_.c_str (), ios::in | ios::binary| ios::ate);
    if (!ifs_.is_open ()) {
        cerr << "open file " << filepath_ << " failed" << endl;
        return;
    }
    // 2 获取文件名称，大小 filename.zip,2334 
    filesize_ = ifs_.tellg ();
    ifs_.seekg (0, ios::beg);
    cout << "open file " << filepath_ << " success." << endl;
    //2 回复消息 MSG_DOWNLOAD_ACCEPT
    char buf[32] = {0};
    sprintf (buf, "%d", filesize_);
    XMsg rmsg;
    rmsg.type = MSG_DOWNLOAD_ACCEPT;
    rmsg.size = strlen (buf)+1;  // +1 是发送 \0
    rmsg.data = buf;
    Write (&rmsg);
}


void XFileServerTask::WriteCB () {
    if (!ifs_.is_open ())
        return;
    // 读取内容到 read_buf_
    ifs_.read (read_buf_, sizeof (read_buf_));
    int len = ifs_.gcount ();
    if (len <= 0) {
        ifs_.close ();
        return;
    }
    Write (read_buf_, len);
    if (ifs_.eof ()) {
        ifs_.close ();
    }
}
void XFileServerTask::ReadCB (void * data, int size) {
    if (!ofs_.is_open () || size <=0||!data)
        return;
    ofs_.write ((char *) data, size);  // data 写入ofs_中
    recv_size_ += size;
    if (recv_size_ == filesize_) {
        cout << "file write end." << endl;
        ofs_.close ();
        XMsg rmsg;
        rmsg.type = MSG_UPLOAD_COMLETE;
        rmsg.size = 3;  // +1 是发送 \0
        rmsg.data = (char *)"OK";
        Write (&rmsg);
    }
}

void XFileServerTask::GetDir (const XMsg * msg) {
    //string dir = "file1,1024;file2,4096;file3.zip,5555";
    if (!msg->data) return;
    string root = msg->data;
    //int len = strlen (msg->data);

    if (root.empty ()) {
        root = "./";
    }
    set_cur_dir (root);
    // cout << "root = "<<  root << endl;
     // string dir = "";
     /// cout <<" in GetDir() dir = " << dir << endl;
    string dirs = GetDirData (root);
    // cout << "after GetDirData in GetDir() dir = " << dirs << endl;
    XMsg rmsg;
    rmsg.type = MSG_DIRLIST;
    rmsg.size = dirs.size ()+1;  // +1 是发送 \0
    rmsg.data = (char *) dirs.c_str ();
    Write (&rmsg);
}

// 处理客户端的上传请求
void XFileServerTask::Upload (const XMsg * msg) {
    // 1 获取文件名和文件大小
    if (!msg->data || !msg ||msg->size <= 0)
        return;

    string str = msg->data;
    cout << "in  XFileServerTask::Upload  str = " << str << endl;
    if (str.empty ()) return;

    int pos = str.find_last_of (',');
    if (pos <= 0)
        return;
    string filename = str.substr (0, pos);
    int sizepos = pos+1;
    if (sizepos >= str.size ())
        return;
    string tmp = str.substr (sizepos, str.size ()-sizepos);

    cout << filename <<"," << tmp << endl;
    filesize_ = atoi (tmp.c_str ());
    // 2 打开本地文件
    string filepath = cur_dir ()+filename;
    ofs_.open (filepath, ios::out | ios::binary);
    if (!ofs_.is_open ()) {
        cout << "openfile " << filepath << " failed"<< endl;
        return;
    }
    cout << "openfile " << filepath << " success." << endl;
    // 3 回复 MSG_UPLOAD_ACCEPT 消息 
    XMsg rmsg;
    rmsg.type = MSG_UPLOAD_ACCEPT;
    rmsg.size = 3;  // +1 是发送 \0
    rmsg.data = (char *)"OK";
    Write (&rmsg);
    // 不接收消息，开始接收文件
    set_is_recv_msg (false);
    recv_size_ = 0;
}


