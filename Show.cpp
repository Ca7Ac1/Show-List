#include "Shows.h"
#include "Formatting.h"

#include <string>

Show::Show(std::string name, int score, int watchedEps, int totalEps) : name{name},
                                                                        score{std::max(std::min(score, 10), 0)},
                                                                        watchedEps{std::max(1, watchedEps)},
                                                                        totalEps{std::max(watchedEps, totalEps)} {}

std::string Show::getName() const
{
    return name;
}

int Show::getScore() const
{
    return score;
}

int Show::getWatched() const
{
    return watchedEps;
}

int Show::getTotal() const
{
    return totalEps;
}

void Show::updateScore(int score)
{
    this->score = std::max(std::min(score, 10), 0);
}

void Show::updateWatched(int ep)
{
    this->totalEps = std::max(this->totalEps, ep);
    this->watchedEps = std::max(0, ep);
}

void Show::updateTotal(int total)
{
    this->totalEps = std::max(this->watchedEps, total);
}

Show::operator std::string() const
{
    return pad(name, kLeftShowPad, kRightShowPad) +
           pad(score, kLeftScorePad, KRightScorePad) +
           pad(watchedEps, kLeftEpisodePad, 0) + "/" + pad(totalEps, 0, kRightEpisodePad);
}

Show &Show::operator++()
{
    updateWatched(watchedEps + 1);
    return *this;
}

Show Show::operator++(int increment)
{
   updateWatched(watchedEps + 1);
   return *this;
}