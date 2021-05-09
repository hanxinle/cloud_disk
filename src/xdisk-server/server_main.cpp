#include <event2/event.h>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <signal.h>
#endif
#include "XThreadPool.h"
#include "XServerTask.h"
#include "XFileServerTask.h"
#include <thread>

using namespace std;

static void ListenCB (int sock, struct sockaddr * addr, int socklen, void* arg) {
    auto task = new XFileServerTask ();
    task->set_sock (sock);
    XThreadPool::Get ()->Dispatch (task);

    cout << "ListenCB in server_main.cpp" << endl;
}

int main (int argc, char * argv[]) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup (MAKEWORD (2, 2), &wsa);
#endif

    int server_port = 8888;
    int thread_count = 10;

    XThreadPool::Get ()->Init (thread_count);
    XThreadPool server_pool;
    server_pool.Init (1);
    auto task = new XServerTask ();
    task->set_server_port (server_port);
    task->ListenCB = ListenCB;
    server_pool.Dispatch (task);
    //XThreadPool::Get ()->Dispatch (task);
    while (1) {
        this_thread::sleep_for (1s);
    }
    return 0;
}


