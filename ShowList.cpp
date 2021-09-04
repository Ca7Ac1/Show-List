#include "Shows.h"
#include "Formatting.h"
#include "File.h"

#include <string>
#include <algorithm>
#include <vector>

const int kAppendDistance = 0;
const int kInsertDistance = 1;
const int kDeleteDistance = 15;
const int kReplaceDistance = 12;

const std::map<int, std::pair<std::string, bool (*)(const Show &, const Show &)>> kSortValues =
    {
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
    this->username = username;
    FileReader userShowReader("./UserShows/" + username + "_Shows.txt");

    while (!userShowReader.isEnd())
    {

        std::string name = userShowReader.readLine();
        int score = std::stoi(userShowReader.readNext());
        int watched = std::stoi(userShowReader.readNext());
        int total = std::stoi(userShowReader.readNext());

        addShow(name, score, watched, total);
        userShowReader.skipLine();
    }
}

ShowList::~ShowList()
{
    FileWriter userShowWriter("UserShows/" + username + "_Shows.txt", true);

    for (Show show : shows)
    {
        userShowWriter.writeLine(show.getName());
        userShowWriter.writeLine(std::to_string(show.getScore()) + " " +
                                 std::to_string(show.getWatched()) + " " +
                                 std::to_string(show.getTotal()));
    }
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
    std::string show = shows[0].getName();
    int bestDistance = showMatch(name, show);

    for (int i = 1; i < shows.size(); i++)
    {
        int currDistance = showMatch(name, shows[i].getName());

        if (currDistance < bestDistance)
        {
            show = shows[i].getName();
            bestDistance = currDistance;
        }
    }

    return show;
}

bool ShowList::hasShow() const
{
    return shows.size() > 0;
}

int ShowList::showMatch(const std::string &input, const std::string &actual) const
{
    std::vector<std::vector<int>> distance(input.size() + 1, std::vector<int>(actual.size() + 1, INT_MAX));

    for (int i = 0; i <= input.size(); i++)
    {
        for (int j = 0; j <= actual.size(); j++)
        {
            if (i == 0)
            {
                distance[i][j] = j * kInsertDistance;
            }
            else if (j == 0)
            {
                distance[i][j] = i * kDeleteDistance;
            }
            else
            {
                distance[i][j] = std::min({distance[i - 1][j] + kDeleteDistance,
                                           distance[i][j - 1] + (i == input.size() ? kAppendDistance : kInsertDistance),
                                           distance[i - 1][j - 1] + (input[i - 1] == actual[j - 1] ? 0 : kReplaceDistance)});
            }
        }
    }

    return distance[input.size()][actual.size()];
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