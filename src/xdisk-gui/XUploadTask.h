#pragma once
#include "XComTask.h"
#include <fstream>

typedef void (*UploadCBFunc) ();
class XUploadTask : public XComTask {

public:
    // 接收消息回调
    virtual bool ReadCB (const XMsg * msg);
    // 连接成功回调
    virtual void ConnectedCB ();

    void set_filepath (std::string path) {
        this->filepath_ = path;
    }
    virtual void WriteCB ();
    // 上传结束成功后的回调
    UploadCBFunc UploadCB = 0;
private:
    // 需要上传的文件路径
    std::string filepath_ = "";
    // 读取文件
    std::ifstream ifs_;
    // 文件大小，暂时不支持大于2G的文件
    int filesize_ = 0;
};

