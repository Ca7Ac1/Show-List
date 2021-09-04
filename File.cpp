#include "File.h"
#include "Formatting.h"

#include <string>
#include <fstream>

FileReader::FileReader(const std::string &path)
{
    file = std::ifstream(path);
}

FileReader::~FileReader()
{
    file.close();
}

std::string FileReader::readNext()
{
    std::string next;
    file >> next;

    return trim(next);
}

std::string FileReader::readLine()
{
    std::string next;
    std::getline(file, next);

    return trim(next);
}

void FileReader::skipLine()
{
    readLine();
}

bool FileReader::isEnd()
{
    file.peek();
    return file.eof() || !file.good();
}

FileWriter::FileWriter(const std::string &path, bool overwrite)
{
    if (overwrite)
    {
        file = std::ofstream(path, std::ofstream::trunc);
    }
    else
    {
        file = std::ofstream(path, std::ofstream::app);
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
