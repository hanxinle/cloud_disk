#include "XComTask.h"
#include "XMsg.h"
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <iostream>
using namespace std;

static void SReadCB (struct bufferevent *bev, void *ctx) {
    auto task = (XComTask *) ctx;
    task->ReadCB ();
}

bool XComTask::ReadCB (const XMsg * msg) {
    cout <<"recved Msg tpye = " << msg->type << "size = "
        << msg->size << endl;
    return true;
}
void  XComTask::ReadCB () {
    if (!is_recv_msg_) {
        int len = bufferevent_read (bev_, read_buf_, sizeof (read_buf_));
        if (len <= 0)
            return;
        ReadCB (read_buf_, len);
        return;
    }

    // 接收消息 XMsgHead
    // 1 接收头部信息
    if (!msg_.data) {
        int headsize = sizeof (XMsgHead);
        int len = bufferevent_read (bev_, &msg_, headsize);
        if (len <= 0)
            return;
        if (len != headsize) {
            cerr << "msg_ head recv error" << endl;
            return;
        }
        // 验证消息头的有效性
        if (msg_.type >= MSG_MAX_TYPE || msg_.size <= 0 ||
            msg_.size > MSG_MAX_SIZE) {
            cerr << "msg head is error" << endl;
            return;
        }
        msg_.data = new char[msg_.size];
    }

    // 确保边缘触发时能读取到所有数据
    while (1) {
        int readsize = msg_.size-msg_.recved;
        if (readsize <= 0) {
            delete msg_.data;
            memset (&msg_, 0, sizeof (msg_));
        }
        int len = bufferevent_read (bev_, msg_.data+msg_.recved, readsize);
        if (len <= 0)
            return;
        msg_.recved += len;
        if (msg_.recved == msg_.size) {
            cout << "recved msg size = " << msg_.size << endl;
            if (!ReadCB (&msg_)) {
                return;
            }
            delete msg_.data;
            memset (&msg_, 0, sizeof (msg_));

        }
    }
}
static void SWriteCB (struct bufferevent *bev, void *ctx) {
    auto task = (XComTask *) ctx;
    task->WriteCB ();
}

void  XComTask::BeginWrite () {
    if (!bev_) return;
    bufferevent_trigger (bev_, EV_WRITE, 0);
}

void XComTask::Close () {
    if (bev_)
        bufferevent_free (bev_);
    bev_ = NULL;
    if (msg_.data) {
        delete msg_.data;
        memset (&msg_, 0, sizeof (msg_));
    }
    delete this;
}

bool XComTask::Write (const void * data, int size) {
    if (!bev_ ||  !data || size <= 0)
        return false;
    int re = bufferevent_write (bev_, data, size);
    if (re != 0) return false;
    return true;
}

bool XComTask::Write (const XMsg * msg) {
    if (!bev_ || !msg || !msg->data || msg->size <= 0)
        return false;


    // 1 写入消息头
    int re = bufferevent_write (bev_, msg, sizeof (XMsgHead));
    if (re != 0) return false;
    // 写入消息内容
    int re1 = bufferevent_write (bev_, msg->data, msg->size);
    if (re1 != 0) return false;

    return true;

}
static void SEventCB (struct bufferevent *bev, short what, void *ctx) {
    cout << "bufferevent SEventCB in XComTask" << endl;
    auto task = (XComTask *) ctx;
    task->EventCB (what);

}

void XComTask::EventCB (short what) {
    if (what & BEV_EVENT_CONNECTED) {
        cout << "BEV_EVENT_CONNECTED" << endl;
        ConnectedCB ();
        // bufferevent_write (bev_, "OK", 3);
    }
    // 退出要处理缓冲内容
    if (what & BEV_EVENT_ERROR) {
        cout<< " BEV_EVENT_ERROR"<< endl;
        Close ();
        //  bufferevent_free (bev_);
    }
    if (what & BEV_EVENT_TIMEOUT) {
        cout<< "BEV_EVENT_TIMEOUT"<< endl;
        Close ();
        //bufferevent_free (bev_);
    }

    if (what & BEV_EVENT_EOF) {
        cout<< " BEV_EVENT_EOF"<< endl;
        Close ();
        //bufferevent_free (bev_);
    }

}

bool XComTask::Init () {
    // 用 buffer_event 建立连接，-1 自动创建 socket
    // 创建 bufferevet 上下文
    // 区分服务端客户端
    int com_sock = this->sock ();
    if (com_sock <= 0) {
        com_sock = -1;
    }

    bev_ = bufferevent_socket_new (base (), com_sock, BEV_OPT_CLOSE_ON_FREE);
    if (!bev_) {
        cerr << "XComTask::Init() bev_ failed." << endl;
    }


    // 设置回调函数，事件类型，超时
    bufferevent_setcb (bev_, SReadCB, SWriteCB, SEventCB, this);
    bufferevent_enable (bev_, EV_READ | EV_WRITE);

    timeval tv = {10,0};

    bufferevent_set_timeouts (bev_, &tv, &tv);

    // 连接服务器
    if (server_ip_.empty ()) {
        return true;
    }
    sockaddr_in sin;
    memset (&sin, 0, sizeof (sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons (server_port_);

    evutil_inet_pton (AF_INET, server_ip_.c_str (), &sin.sin_addr.s_addr);

    int re = bufferevent_socket_connect (bev_, (sockaddr*) &sin, sizeof (sin));
    if (re != 0) {
        return false;
    }
    return true;
}
