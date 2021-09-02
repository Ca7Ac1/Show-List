#include "File.h"

#include <string>
#include <fstream>

File::File(std::string path)
{
    file.open(path);
}

File::~File()
{
    file << std::flush;
    file.close();
}

std::string File::readNext()
{
    std::string next;
    file >> next;

    return next;
}

void File::skipLine()
{
    std::string skipped;
    std::getline(file, skipped);
}

void File::writeLine(const std::string &line)
{
    file << line << '\n';
}

bool File::end()
{
    return file.eof();
}