#pragma once
#include "XComTask.h"
typedef void (*DirCBFunc) (std::string dirs);
class XDirTask : public XComTask {
public:
    // 接收消息回调
    virtual bool ReadCB (const XMsg * msg);
    // 连接成功回调
    void ConnectedCB ();

    // 获取目录后调用的回调 
    DirCBFunc DirCB = 0;
    void set_server_dir (std::string root) {
        this->server_dir_ = root;
    }
private:
    std::string server_dir_ = "";
};

