#pragma once
#ifdef _WIN32
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif
#else
#define XCOM_API
#endif

#include "XTask.h"
#include "XMsg.h"
#include <string>
class XCOM_API XComTask : public XTask {
public:
    virtual bool Init ();
    virtual void Close ();
    void set_server_ip (std::string ip) {
        this->server_ip_ = ip;
    }

    void set_server_port (int port) {
        this->server_port_ = port;
    }
    struct bufferevent * bev () {
        return this->bev_;
    }

    int server_port () {
        return this->server_port_;
    }

    std::string server_ip () {
        return this->server_ip_;
    }
    virtual void EventCB (short what);
    // 连接成功的消息，由业务类重载
    virtual void ConnectedCB () { };
    // 激活写入回调
    virtual void BeginWrite ();
    // 写入数据回调
    virtual void WriteCB () { };
    // 发送消息
    virtual bool Write (const XMsg * msg);
    virtual bool Write (const void * data, int size);
    // 当关闭消息接收时，数据将发送到此函数，由业务模块重载
    virtual void ReadCB (void * data, int size) { }
    // 接收到消息的回调，由业务类重载
    // 返回true正常，返回false突出当前的消息处理,不处理下一条消息
    virtual bool ReadCB (const XMsg * msg) = 0;
    // 读取数据回调函数
    virtual void ReadCB ();
    void set_is_recv_msg (bool isrecv) {
        this->is_recv_msg_ = isrecv;
    }
protected:
    char read_buf_[40960] = {0};
private:
    struct bufferevent * bev_ = 0;
    std::string server_ip_ = "";
    int server_port_ = 0;
    // 数据包缓存
    XMsg msg_;
    // 是否接收消息，接收的话会调用  ReadCB (const XMsg * msg)
    // 不接收调用  ReadCB (void * data,int size )
    bool is_recv_msg_ = true;
};

