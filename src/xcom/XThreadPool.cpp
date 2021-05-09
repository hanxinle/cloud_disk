#include "XThreadPool.h"
#include "XTask.h"
#include "XThread.h"
#include <iostream>
#include <thread>

using namespace std;


// 初始化线程池并启动线程
void XThreadPool::Init (int thread_count) {
    this->thread_count_ = thread_count;
    this->last_thread_ = -1;
    for (int i = 0; i < thread_count; ++i) {
        XThread * t = new XThread ();
        t->id_ = i + 1;
        cout << "create thread " << i << endl;
        // 启动线程并加入线程池
        t->Start ();
        threads_.push_back (t);
        this_thread::sleep_for (10ms);
    }
}
// 分发线程
void XThreadPool::Dispatch (XTask * task) {
    if (task == nullptr)
        return;
    int thread_id = (last_thread_ + 1) % thread_count_;

    last_thread_ = thread_id;

    XThread * t = threads_[thread_id];
    t->AddTask (task);
    t->Activate ();

}

