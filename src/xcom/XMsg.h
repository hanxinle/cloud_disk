#ifndef XMSG_H
#define XMSG_H

#ifdef _WIN32
#ifdef XCOM_EXPORTS
#define XCOM_API __declspec(dllexport)
#else
#define XCOM_API __declspec(dllimport)
#endif
#else
#define XCOM_API
#endif

// 用来验证类型正确,消息最大字节数
#define MSG_MAX_SIZE 1000000

enum MsgType {
    MSG_GETDIR,             // 请求目录
    MSG_DIRLIST,            // 返回目录列表
    MSG_UPLOAD_INFO,        // 上传文件的信息
    MSG_UPLOAD_ACCEPT,
    MSG_UPLOAD_COMLETE,

    MSG_DOWNLOAD_INFO,      // 请求下载文件
    MSG_DOWNLOAD_ACCEPT,    // 
    MSG_DOWNLOAD_COMPLETE,  // 客户端下载成功


    MSG_MAX_TYPE,           // 用来验证类型正确
};

struct XCOM_API XMsgHead {
    MsgType type;
    int size = 0;
};

// 约定每个消息必须包含内容，没有内容使用“OK”
struct XCOM_API XMsg : public XMsgHead {
    char * data = 0;       // 存储消息内容
    int  recved = 0;       // 已经接收的消息字节数
};
















#endif // !XMSG_H
