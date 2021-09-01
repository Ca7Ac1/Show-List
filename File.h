#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

class File
{
    std::fstream file;

public:
    File(std::string);
    ~File();
    std::string readNext();
    void skipLine();
    void writeLine(const std::string &);
};

#endif
