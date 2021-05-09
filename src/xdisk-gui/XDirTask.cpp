#include "XDirTask.h"
#include <iostream>
using namespace std;

bool XDirTask::ReadCB (const XMsg * msg) {
    switch (msg->type) {
    case MSG_DIRLIST:
        cout << "MSG_DIRLIST" << endl;
        DirCB (msg->data);
        break;
    default:
        break;
    }
    return true;
}

void XDirTask::ConnectedCB () {
    XMsg msg;
    msg.type = MSG_GETDIR;
    msg.size = server_dir_.size ()+1;
    msg.data = (char*) server_dir_.c_str ();
    Write (&msg);
}
