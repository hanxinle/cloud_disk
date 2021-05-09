#ifndef XSERVER_TASK_H
#define XSERVER_TASK_H

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

typedef void (*ListenCBFunc)(int sock, struct sockaddr * addr, int socklen, void* arg);


class XCOM_API XServerTask : public XTask {
public:
    virtual bool Init ();
    // 业务逻辑，要用户传进来，不能在cpp中定义
    ListenCBFunc ListenCB = nullptr;

    void set_server_port (int port) {
        server_port_ = port;

    }
private:
    int server_port_ = 0;
};

#endif
