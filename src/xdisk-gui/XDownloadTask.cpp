#include "XDownloadTask.h"
#include<iostream>
using namespace std;
bool XDownloadTask::ReadCB (const XMsg * msg) {
    switch (msg->type) {
    case MSG_DOWNLOAD_ACCEPT:
        set_is_recv_msg (false);
        if (msg->data)
            filesize_ = atoi (msg->data);
        else {
            Close ();
            return false;
        }
        break;
    default:
        break;
    }
    return true;
}
void XDownloadTask::ConnectedCB () {
    if (filepath_.empty ()) {
        Close ();
        return;
    }
    // 3 发送下载文件请求
    string data = filepath_;
    int pos = filepath_.find_last_of ('/');
    if (pos < 0)
        pos = 0;
    string filename = filepath_.substr (pos, filepath_.size ()-pos);
    string path = localdir_ + filename;
    ofs_.open (path, ios::out | ios::binary);

    if (!ofs_.is_open ()) {
        cerr << "open file " << path << " failed" << endl;
        return;
    }
    cout << "open file " << path << " success." << endl;

    XMsg msg;
    msg.type = MSG_DOWNLOAD_INFO;
    msg.data = (char *) data.c_str ();
    msg.size = data.size ()+1;
    Write (&msg);
}


void XDownloadTask::ReadCB (void * data, int size) {
    if (!ofs_.is_open () || size <=0||!data)
        return;
    ofs_.write ((char *) data, size);  // data 写入ofs_中
    recv_size_ += size;
    if (recv_size_ == filesize_) {
        // 下载成功后
        if (DownloadCB)
            DownloadCB ();
        cout << "file write end." << endl;
        ofs_.close ();
        XMsg rmsg;
        rmsg.type = MSG_DOWNLOAD_COMPLETE;
        rmsg.size = 3;  // +1 是发送 \0
        rmsg.data = (char *)"OK";
        Write (&rmsg);
    }
}


