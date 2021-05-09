#include "xdiskgui.h"
#include <QtWidgets/QApplication>
#include <Windows.h>
int main (int argc, char *argv[]) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup (MAKEWORD (2, 2), &wsa);
#endif

    QApplication a (argc, argv);
    xdiskgui w;
    w.show ();
    return a.exec ();
}
