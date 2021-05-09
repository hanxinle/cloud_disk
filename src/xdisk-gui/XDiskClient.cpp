#include "XDiskClient.h"
#include "XComTask.h"
#include "XThreadPool.h"
#include "XDirTask.h"
#include "XUploadTask.h"
#include "XDownloadTask.h"
#include <iostream>
using namespace std;

bool XDiskClient::Init () {
    XThreadPool::Get ()->Init (10);
    return true;
}

static void DirCB (string dirs) {
    cout << dirs << endl;
    XDiskClient::Get ()->SDir (dirs);
}

static void UploadCB () {
    cout << "UploadCB" << endl;
    XDiskClient::Get ()->SUploadComplete ();
}

static void DownloadCB () {
    cout << "DownloadCB" << endl;
    XDiskClient::Get ()->SDownloadComplete ();
}

void XDiskClient::GetDir () {
    cout << "XDiskClient::Getdir()" << endl;
    cout << server_ip_ << " "  << server_port_
        << "  " << server_dir_ << endl;

    auto task = new XDirTask ();
    task->set_server_ip (server_ip_);
    task->set_server_port (server_port_);
    task->set_server_dir (server_dir_);
    task->DirCB = DirCB;
    XThreadPool::Get ()->Dispatch (task);
}

void XDiskClient::Upload (std::string filepath) {
    auto task = new XUploadTask ();
    task->set_server_ip (server_ip_);
    task->set_server_port (server_port_);
    task->set_filepath (filepath);
    task->UploadCB = UploadCB;
    XThreadPool::Get ()->Dispatch (task);
}
// 文件下载
// param1 远端文件相对路径
// param2 本地存储的目录
void XDiskClient::Download (std::string serverpath, std::string localdir) {
    auto task = new XDownloadTask ();
    task->set_server_ip (server_ip_);
    task->set_server_port (server_port_);
    task->set_filepath (serverpath);
    task->set_local_dir (localdir);
    task->DownloadCB = DownloadCB;
    XThreadPool::Get ()->Dispatch (task);
}


