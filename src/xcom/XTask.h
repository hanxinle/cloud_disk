#ifndef XTASK_H
#define XTASK_H

#ifdef _WIN32
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif
#else
#define XCOM_API
#endif

class XCOM_API XTask {
public:
    virtual bool Init () = 0;
    int thread_id () { return thread_id_; }
    struct event_base * base () { return base_; }
    int sock () { return sock_; }

    void set_thread_id (int thread_id) {
        this->thread_id_ = thread_id;
    }

    void set_sock (int sock) {
        this->sock_ = sock;
    }
    void set_event_base (struct event_base * base) {
        this->base_ = base;
    }
private:
    struct  event_base * base_ = 0;
    int sock_ = 0;
    int thread_id_ = 0;
};

#endif