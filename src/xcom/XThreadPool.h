#ifndef XTHREADPOOL_H
#define XTHREADPOOL_H

#ifdef _WIN32
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif
#else
#define XCOM_API
#endif
#include <vector>
class XThread;
class XTask;
class XCOM_API XThreadPool {
public:
    static XThreadPool * Get () {
        static XThreadPool p;
        return &p;
    }

    // 初始化线程池并启动线程
    void Init (int thread_count);
    // 分发线程
    void Dispatch (XTask * task);
    XThreadPool () { };
private:
    int thread_count_ = 0;
    int last_thread_ = 0;
    std::vector<XThread*> threads_;


};

#endif