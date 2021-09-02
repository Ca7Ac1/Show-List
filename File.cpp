#include "File.h"

#include <string>
#include <fstream>

FileReader::FileReader(std::string path)
{
    file.open(path);
}

FileReader::~FileReader()
{
    file.close();
}

std::string FileReader::readNext()
{
    std::string next;
    file >> next;

    return next;
}

void FileReader::skipLine()
{
    std::string skipped;
    std::getline(file, skipped);
}

bool FileReader::isEnd()
{
    return file.eof();
}

FileWriter::FileWriter(std::string path) : FileWriter(path, false) {}

FileWriter::FileWriter(std::string path, bool overwrite)
{
    if (overwrite)
    {
        file.open(path, std::ofstream::trunc);
    }
    else
    {
        file.open(path, std::ofstream::app);
    }
}

FileWriter::~FileWriter()
{
    file << std::flush;
    file.close();
}

void FileWriter::writeLine(const std::string &line)
{
    file << line << '\n';
}
