#include "XThread.h"
#include <event2/event.h>
#include <iostream>
#include <thread>

#include "XTask.h"
#include "XThread.h"
#ifdef _WIN32
#else
#include <untistd.h>
#endif

using namespace std;

static void NotifyCB (evutil_socket_t fd, short which, void * arg) {
    XThread * t = (XThread*) arg;
    t->Notify (fd, which);
}

void  XThread::Activate () {
#ifdef _WIN32
    int  re = send (this->notify_send_fd_, "c", 1, 0);
#else
    int re = write (this->notify_send_fd_, "c", 1);
#endif
    if (re <= 0) {
        cerr << "XThread::Activate() failed" << endl;
    }
}
void XThread::Notify (evutil_socket_t fd, short which) {
    // 水平触发，只要没有接收完成，会再其次进来
    char buf[2] = {0};
#ifdef _WIN32
    int re = recv (fd, buf, 1, 0);
#else 
    int re = read (fd, buf, 1);
#endif
    if (re < 0)
        return;
    cout << id_ << " thread " << buf << endl;
    XTask * task = nullptr;
    // 获取任务，并且初始化任务
    tasks_mutex_.lock ();
    if (tasks_.empty ()) {
        tasks_mutex_.unlock ();
        return;
    }
    task = tasks_.front ();
    tasks_.pop_front ();
    tasks_mutex_.unlock ();
    task->Init ();
}

void XThread::Start () {
    Setup ();
    // 启动线程
    thread th (&XThread::Main, this);

    th.detach ();
}

// 初始化 base_,创建监听激活线程的事件
bool XThread::Setup () {

    // windows用配对socket，Linux用管道
#ifdef _WIN32
    evutil_socket_t fds[2];
    if (evutil_socketpair (AF_INET, SOCK_STREAM, 0, fds) < 0) {
        cout << "evutil_socketpair failure"  << endl;
        return false;
    }
    // 设置成非阻塞
    evutil_make_socket_nonblocking (fds[0]);
    evutil_make_socket_nonblocking (fds[1]);
#else
    int fds[2];
    if (pipe (fds)) {
        cerr << "pipe failed" << endl;
        return false;
    }
#endif 
    // 读取并定到 event 事件中，写入要保存
    notify_send_fd_ = fds[1];
    // 创建libevent 上下文
    event_config * ev_conf = event_config_new ();
    event_config_set_flag (ev_conf, EVENT_BASE_FLAG_NOLOCK);
    this->base_ = event_base_new_with_config (ev_conf);
    event_config_free (ev_conf);
    if (!base_) {
        cerr << "event_base_new_with_config in Thread::Setup failure." << endl;
        return false;
    }
    // 添加管道监听事件，用于激活线程执行任务
    event * ev = event_new (base_, fds[0], EV_READ | EV_PERSIST, NotifyCB, this);
    event_add (ev, 0);
    return true;
}
void XThread::Main () {
    cout << id_ << " XThread::Main() begin." << endl;
    if (!base_) {
        cerr << "XThread::Main() failed. bev_ is NULL" << endl;
        cerr << "In windows set WSAstarup(MAKEWORD(2,2)) may failed" << endl;
        return;
    }
    event_base_dispatch (base_);
    event_base_free (base_);
    cout << id_ << " XThread::Main() end." << endl;
}
void XThread::AddTask (XTask *t) {
    if (t == nullptr)
        return;
    t->set_event_base (this->base_);
    tasks_mutex_.lock ();
    tasks_.push_back (t);
    tasks_mutex_.unlock ();
}

XThread::XThread () { }

XThread::~XThread () { }
