#pragma once
#include <Qobject>
#include <string>

class XDiskClient :public QObject {
    Q_OBJECT;
public:
    static XDiskClient* Get () {
        static XDiskClient x;
        return &x;
    }

    // 初始化，包括线程池
    bool Init ();
    // 获取目录下的文件列表，只是发送请求消息到服务端
    void GetDir ();
    // 文件上传
    void Upload (std::string filepath);
    // 文件下载
    // param1 远端文件相对路径
    // param2 本地存储的目录
    void Download (std::string serverpath, std::string localdir);

    void set_server_ip (std::string ip) {
        this->server_ip_ = ip;
    }

    void set_server_port (int port) {
        this->server_port_ = port;
    }

    void set_server_dir (std::string root) {
        this->server_dir_ = root;
    }

signals:
    void SDir (std::string dirs);
    void SUploadComplete ();
    void SDownloadComplete ();

private:
    XDiskClient () { };

    std::string server_ip_ = "";
    std::string server_dir_ = "";
    int server_port_ = 0;

};

