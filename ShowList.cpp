#include "Shows.h"
#include "Formatting.h"

#include <string>
#include <algorithm>

const std::map<int, std::pair<std::string, bool (*)(const Show &, const Show &)>> kSortValues =
    {
        // Name 2. Score 3. Episodes watched 4. Episodes left 5. None
        {1, {"Name", cmprName}},
        {2, {"Score", cmprScore}},
        {3, {"Episodes watched", cmprWatched}},
        {4, {"Episodes left", cmprUnwatched}}};

bool cmprName(const Show &a, const Show &b)
{
    return a.getName() < b.getName();
}
bool cmprScore(const Show &a, const Show &b)
{
    return a.getScore() < b.getScore();
}
bool cmprWatched(const Show &a, const Show &b)
{
    return a.getWatched() < b.getWatched();
}
bool cmprUnwatched(const Show &a, const Show &b)
{
    return (a.getTotal() - a.getWatched()) < (b.getTotal() - b.getWatched());
}

ShowList::ShowList(const std::string &username) : sortPrimary{-1}, sortSecondary{-1}, descendingPrimary{true}, descendingSecondary{true}
{
}

void ShowList::addShow(const std::string &name, int score, int watched, int total)
{
    shows.push_back(Show(name, score, watched, total));
    sort();
}

Show &ShowList::getShow(const std::string &name)
{
    for (Show &show : shows)
    {
        if (show.getName() == name)
        {
            return show;
        }
    }

    throw std::exception();
}

std::string ShowList::findShow(const std::string &name) const
{
    return name;
}

void ShowList::sort(int sortPrimary, int sortSecondary, bool descendingPrimary, bool descendingSecondary)
{
    this->sortPrimary = sortPrimary;
    this->sortSecondary = sortSecondary;
    this->descendingPrimary = descendingPrimary;
    this->descendingSecondary = descendingSecondary;

    sort();
}

void ShowList::sort()
{
    if (kSortValues.find(sortSecondary) != kSortValues.end())
    {
        std::stable_sort(shows.begin(), shows.end(), kSortValues.at(sortSecondary).second);

        if (descendingSecondary == !descendingPrimary)
        {
            std::reverse(shows.begin(), shows.end());
        }
    }

    if (kSortValues.find(sortPrimary) != kSortValues.end())
    {
        std::stable_sort(shows.begin(), shows.end(), kSortValues.at(sortPrimary).second);

        if (descendingPrimary)
        {
            std::reverse(shows.begin(), shows.end());
        }
    }
}

ShowList::operator std::string() const
{
    std::string list = header();

    for (const Show &show : shows)
    {
        list += "\n" + (std::string)show;
    }

    return list + "\n";
}