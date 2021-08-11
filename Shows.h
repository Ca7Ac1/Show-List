#ifndef SHOWS_H
#define SHOWS_H

#include <string>
#include <vector>
#include <map>

class Show
{
    std::string name;
    int score;
    int watchedEps;
    int totalEps;

public:
    Show(std::string, int, int, int);
    //~Show();

    std::string getName() const;
    int getScore() const;
    int getWatched() const;
    int getTotal() const;
    void updateScore(int);
    void updateWatched(int);
    void updateTotal(int);
    operator std::string() const;
    Show &operator++();
    Show operator++(int);
};

extern const std::map<int, std::pair<std::string, bool (*)(const Show &, const Show &)>> kSortValues;

bool cmprName(const Show &, const Show &);
bool cmprScore(const Show &, const Show &);
bool cmprWatched(const Show &, const Show &);
bool cmprUnwatched(const Show &, const Show &);

class ShowList
{
    std::vector<Show> shows;
    int sortPrimary;
    int sortSecondary;
    bool descendingPrimary;
    bool descendingSecondary;

    int showMatch(const std::string &, const std::string &) const;

public:
    ShowList(const std::string &);

    void addShow(const std::string &, int, int, int);
    Show &getShow(const std::string &);
    std::string findShow(const std::string &) const;
    void sort(int, int, bool, bool);
    void sort();
    operator std::string() const;
};

#endif