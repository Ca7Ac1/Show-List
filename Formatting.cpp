#include "Formatting.h"
#include <iostream>

#include <string>

const int kLeftShowPad = 7;
const int kRightShowPad = 57;

const int kLeftScorePad = 7;
const int KRightScorePad = 32;

const int kLeftEpisodePad = 7;
const int kRightEpisodePad = 17;

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

void clear()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; 
}