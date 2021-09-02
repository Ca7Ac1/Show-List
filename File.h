#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

class FileReader
{
    std::ifstream file;

public:
    FileReader(std::string);
    ~FileReader();
    std::string readNext();
    void skipLine();
    bool isEnd();
};

class FileWriter
{
    std::ofstream file;

public:
    FileWriter(std::string);
    FileWriter(std::string, bool);
    void writeLine(const std::string &);
};

#endif
