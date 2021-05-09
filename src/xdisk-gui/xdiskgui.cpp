#include "xdiskgui.h"
#include "XDiskClient.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
using namespace std;
xdiskgui::xdiskgui (QWidget *parent)
    : QWidget (parent) {
    ui.setupUi (this);
    XDiskClient::Get ()->Init ();
    // 注册信号支持的类型
    qRegisterMetaType <std::string> ("std::string");
    //绑定目录获取的信号
    QObject::connect (XDiskClient::Get (), SIGNAL (SDir (std::string)),
                      this, SLOT (UpdateDir (std::string)));
    QObject::connect (XDiskClient::Get (), SIGNAL (SUploadComplete ()),
                      this, SLOT (Refresh ()));
    QObject::connect (XDiskClient::Get (), SIGNAL (SDownloadComplete ()),
                      this, SLOT (DownloadComplete ()));
    Refresh ();
}
void xdiskgui::DownloadComplete () {
    QMessageBox::information (this, "", "DownloadComplete");
}
void xdiskgui::UpdateDir (std::string dirs) {
    QString str = dirs.c_str ();
    str = str.trimmed ();
    if (str.isEmpty ())
        return;
    QStringList filestr = str.split (';');
    ui.filelistWidget->setRowCount (filestr.size ());
    for (int i = 0; i < filestr.size (); i++) {
        QStringList fileinfo = filestr[i].split (',');
        if (fileinfo.size () !=2) continue;
        ui.filelistWidget->setItem (i, 0, new QTableWidgetItem (fileinfo[0]));
        ui.filelistWidget->setItem (i, 1, new QTableWidgetItem (tr ("%1Byte").arg (fileinfo[1])));

    }

}


void xdiskgui::Refresh () {
    //QMessageBox::information (this, "", "刷新");
    // 服务器路径、IP、端口号
    UpdateServerInfo ();
    //string ip = ui.ipEdit->text ().toStdString ();
    //string dir = ui.dirEdit->text ().toStdString ();
    //int port = ui.portBox->value ();
    //XDiskClient::Get ()->set_server_ip (ip);
    //XDiskClient::Get ()->set_server_port (port);
    //XDiskClient::Get ()->set_server_dir (dir);
    XDiskClient::Get ()->GetDir ();
    // 1 连接服务器

    // 2 设置回调(门面模式)
}

void xdiskgui::Upload () {
    QString filename = QFileDialog::getOpenFileName (this, QString::fromLocal8Bit ("请选择文件"));
    if (filename.isEmpty ())
        return;
    UpdateServerInfo ();
    XDiskClient::Get ()->Upload (filename.toStdString ());
    ///* ui.filelistWidget->insertRow (0);
    // ui.filelistWidget->setItem (0, 0, new QTableWidgetItem (filename));
    // ui.filelistWidget->setItem (0, 1, new QTableWidgetItem (tr ("%1Byte").arg (1900)));
    // */
}

void  xdiskgui::Download () {
    // 用户选择下载的文件和路径
    UpdateServerInfo ();
    int row = ui.filelistWidget->currentRow ();
    if (row < 0) {
        QMessageBox::information (this, "", QString::fromLocal8Bit ("请选择要下载的文件"));
        return;
    }
    // 获取选择的文件名
    auto item = ui.filelistWidget->item (row, 0);
    string filename = item->text ().toStdString ();
    // 获取下载路径
    QString localpath = QFileDialog::getExistingDirectory (this, QString::fromLocal8Bit ("请选择下载路径"));

    if (localpath.isEmpty ())
        return;
    string filepath = ui.dirEdit->text ().toStdString ();
    filepath += "/";
    filepath += filename;
    XDiskClient::Get ()->Download (filepath, localpath.toStdString ());

}

void xdiskgui::UpdateServerInfo () {
    string ip = ui.ipEdit->text ().toStdString ();
    string dir = ui.dirEdit->text ().toStdString ();
    int port = ui.portBox->value ();
    XDiskClient::Get ()->set_server_ip (ip);
    XDiskClient::Get ()->set_server_port (port);
    XDiskClient::Get ()->set_server_dir (dir);
}
