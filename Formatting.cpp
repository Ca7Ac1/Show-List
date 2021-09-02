#include "Formatting.h"
#include <iostream>

#include <string>

const std::string kAuthenticationFile = "UserInfo.txt";

const int kLeftShowPad = 7;
const int kRightShowPad = 57;

const int kLeftScorePad = 7;
const int KRightScorePad = 32;

const int kLeftEpisodePad = 7;
const int kRightEpisodePad = 17;

const std::string kWhitespace = " \n\r\t\f\v ";

std::string pad(int item, int left, int right)
{
    return pad(std::to_string(item), left, right);
}

std::string pad(std::string str, int left, int right)
{
    if (left < 0 || right < 0)
    {
        throw std::exception();
    }

    str = str.insert(0, left, ' ');
    str = str.append(std::max(0, (int)(right - str.size())), ' ');

    return str;
}

std::string header()
{
    return pad("Shows", kLeftShowPad, kRightShowPad) +
           pad("Score", kLeftScorePad, KRightScorePad) +
           pad("Episodes", kLeftEpisodePad, kRightEpisodePad);
}

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(kWhitespace);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(kWhitespace);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

void clear()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; 
}