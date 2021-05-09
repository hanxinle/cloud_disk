#pragma once
#include "XComTask.h"
#include <fstream>
typedef void (*DownloadCBFunc) ();
class XDownloadTask : public XComTask {
public:
    // 接收消息回调
    virtual void ReadCB (void * data, int size);
    virtual bool ReadCB (const XMsg * msg);
    virtual void ConnectedCB ();
    DownloadCBFunc DownloadCB = 0;
    void set_filepath (std::string path) {
        this->filepath_ = path;
    }


    void set_local_dir (std::string localdir) {
        this->localdir_ = localdir;
    }
private:
    // 需要下载的文件的相对路径
    std::string filepath_;
    // 下载到本地的目录
    std::string localdir_;
    // 写入下载的文件
    std::ofstream ofs_;
    // 文件大小
    int filesize_ = 0;
    // 客户已经下载大小
    int recv_size_ = 0;

};

