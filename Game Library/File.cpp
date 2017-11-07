#include "File.hpp"
#include "StringSupport.hpp"
#include "GameError.hpp"
#include "Globals.hpp"
#include <iostream>


static char buffer[1024];


File::File(const std::string& filename)
    : _filename(filename)
{
    __gGMLastErrorPlace = "File::File()";

    std::string path = GetFilepath(filename);
    
    if (path.size() == 0) {
        throw GameError("ファイル \"%s\" が見つかりません。", filename.c_str());
    }
    
    fp = fopen(path.c_str(), "r");
    if (!fp) {
        throw GameError("ファイル \"%s\" のオープンに失敗しました。", filename.c_str());
    }
}

File::~File()
{
    fclose(fp);
}

long File::GetPos()
{
    return ftell(fp);
}

bool File::IsEOF()
{
    return (feof(fp) != 0);
}

int File::Read(unsigned char* buffer, int size)
{
    size_t bytesRead = fread(buffer, 1, size, fp);
    return (int)bytesRead;
}

bool File::ReadLine(std::string& str)
{
    if (!fgets(buffer, 1024, fp)) {
        return false;
    }
    size_t length = strlen(buffer);
    if (iscntrl(buffer[length])) {
        buffer[length--] = '\0';
        if (iscntrl(buffer[length])) {
            buffer[length] = '\0';
        }
    }
    str = buffer;
    return true;
}

bool File::ReadByte(unsigned char& byte)
{
    if (IsEOF()) {
        return false;
    }
    byte = (unsigned char)fgetc(fp);
    return true;
}

bool File::PeekByte(unsigned char& byte)
{
    if (IsEOF()) {
        return false;
    }
    long pos = ftell(fp);
    byte = (unsigned char)fgetc(fp);
    fseek(fp, pos, SEEK_SET);
    return true;
}

bool File::Seek(long pos)
{
    return (fseek(fp, pos, SEEK_SET) == 0);
}

bool File::SkipByte()
{
    if (IsEOF()) {
        return false;
    }
    fseek(fp, 1, SEEK_CUR);
    return true;
}

