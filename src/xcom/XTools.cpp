#include "XTools.h"
#ifdef _WIN32
#include <io.h>
#endif
#include <iostream>
using namespace std;


XCOM_API std::string GetDirData (std::string path) {
    //  cout << "GetDirData path = " <<path<< endl;
    string data = "";



#ifdef _WIN32
    // 存储文件信息
    _finddata_t file;
    string dirpath = path+"/*.*";
    //目录上下文
    intptr_t dir = _findfirst (dirpath.c_str (), &file);
    if (dir < 0)
        return data;
    do {
        // 暂时不处理子目录
        if (file.attrib & _A_SUBDIR)
            continue;
        char  buf[1024] = {0};
        sprintf (buf, "%s,%u;", file.name, file.size);
        data += buf;

    } while (_findnext (dir, &file) ==  0);
#else

#endif
    //去掉结尾的分号
    if (!data.empty ()) {
        data = data.substr (0, data.size ()-1);
    }
    //  cout << "GetDirData data = "<<data << endl;
    return data;
}


