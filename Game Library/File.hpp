#ifndef __FILE_HPP__
#define __FILE_HPP__

#include <string>
#include <cstdio>

// TODO: Fileクラスについてドキュメントを書く。サンプルを作る。

class File
{
    FILE    *fp;
    std::string _filename;
    
public:
    File(const std::string& filename);
    ~File();
    
public:
    long    GetPos();
    bool    IsEOF();
    bool    PeekByte(unsigned char& byte);
    int     Read(unsigned char* buffer, int size);
    bool    ReadByte(unsigned char& byte);
    bool    ReadLine(std::string& str);
    bool    Seek(long pos);
    bool    SkipByte();
};

#endif  //#ifndef __TEXT_FILE_HPP__
