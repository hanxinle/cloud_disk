#include "XServerTask.h"
#include <event2/event.h>
#include <event2/listener.h>
#include <iostream>
using namespace std;

static void SListenCB (struct evconnlistener *evc, evutil_socket_t client_socket, struct sockaddr * client_addr, int socklen, void * arg) {
    cout << "XServerTask SListenCB " << endl;
    auto task = (XServerTask *) arg;
    if (nullptr != task->ListenCB) {
        task->ListenCB (client_socket, client_addr, socklen, arg);
    }
    else {
        cerr << "Please set callback function ListenCB" << endl;
    }

}

bool XServerTask::Init () {
    if (server_port_ <  0) {
        std::cerr << "XServerTask::Init server_port_ < 0" << std::endl;
        return false;
    }
    // 监听端口
    sockaddr_in sin;
    memset (&sin, 0, sizeof (sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons (server_port_);

    auto evc = evconnlistener_new_bind (base (), SListenCB, this,
                                        LEV_OPT_REUSEABLE |
                                        LEV_OPT_CLOSE_ON_FREE,
                                        10,
                                        (sockaddr*) &sin,
                                        sizeof (sin));

    if (!evc) {
        cerr << "Listen port " << server_port_ << " failed" << endl;
        return false;
    }
    cout << "Listen port " << server_port_ << " success." << endl;
    return true;
}
