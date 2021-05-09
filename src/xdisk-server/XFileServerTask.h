#pragma once
#ifndef XFILESERVER_H
#define XFILESERVER_H
#include "XComTask.h"
#include <fstream>
#include <mutex>
class XFileServerTask :public XComTask {
public:
    virtual bool ReadCB (const XMsg * msg);
    virtual void ReadCB (void * data, int size);
    virtual void WriteCB ();
    static void set_cur_dir (std::string dir) {
        cur_dir_mux_.lock ();
        cur_dir_ = dir;
        cur_dir_mux_.unlock ();
    }

    static std::string cur_dir () {
        cur_dir_mux_.lock ();
        std::string dir = cur_dir_;
        cur_dir_mux_.unlock ();
        return dir;
    }
private:
    // 处理目录获取的消息，返回目录列表
    void GetDir (const XMsg * msg);
    // 处理客户端上传请求
    void Upload (const XMsg * msg);
    // 处理客户端下载请求
    void Download (const XMsg * msg);

    // 文件大小
    int filesize_ = 0;
    // 客户已经上传的大小
    int recv_size_ = 0;
    // 当前路径
    static std::string cur_dir_;
    static std::mutex cur_dir_mux_;
    // 写入上传的文件
    std::ofstream ofs_;
    std::string filepath_;
    // 读取文件
    std::ifstream ifs_;


};


#endif

