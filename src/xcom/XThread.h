#ifndef XTHREAD_H
#define XTHREAD_H

#include <event2/event.h>
#include <list>
#include <mutex>
class XTask;
class XThread {
public:
    // 启动线程
    void Start ();
    void Main ();
    bool Setup ();
    void Notify (evutil_socket_t fd, short which);
    void Activate ();
    void AddTask (XTask *);
    XThread ();
    ~XThread ();
    // 线程id
    int id_ = 0;
private:
    int notify_send_fd_ = 0;
    struct event_base * base_ = 0;
    std::list<XTask*> tasks_;
    std::mutex tasks_mutex_;
};

#endif
