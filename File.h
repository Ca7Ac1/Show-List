#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>

class FileReader
{
    std::ifstream file;

public:
    FileReader(const std::string &);
    ~FileReader();
    std::string readNext();
    std::string readLine();
    void skipLine();
    bool isEnd();
};

class FileWriter
{
    std::ofstream file;

public:
    FileWriter(const std::string &, bool = false);
    ~FileWriter();
    void writeLine(const std::string &);
};

#endif
