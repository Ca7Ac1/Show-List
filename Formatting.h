#ifndef FORMATTING_H
#define FORMATTING_H

#include <string>

extern const int kLeftShowPad;
extern const int kRightShowPad;

extern const int kLeftScorePad;
extern const int KRightScorePad;

extern const int kLeftEpisodePad;
extern const int kRightEpisodePad;

std::string pad(int, int, int);
std::string pad(std::string, int, int);
std::string header();
std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::string trim(const std::string &s);
void clear();

#endif