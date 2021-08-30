#include "Authentication.h"
#include "Shows.h"
#include "Formatting.h"

#include <iostream>
#include <string>

int main()
{
    std::cin.exceptions(std::ios_base::failbit | std::ios_base::badbit);

    std::string username;
    std::string password;

    std::cout << "---------------------Welcome to your show list---------------------";
    std::cout << "\nPlease enter your username (or create a new username): ";
    std::cin >> username;
    std::cout << "Please enter your password (or create a new password): ";
    std::cin >> password;

    while (!authenticate(username, password))
    {
        std::cout << "\nIncorrect credentials, please retry\nEnter your username: ";
        std::cin >> username;
        std::cout << "\nPlease enter your password: ";
        std::cin >> password;
    }

    ShowList showList = ShowList(username);
    bool finished = false;

    while (!finished)
    {
        clear();

        try
        {
            int response;

            std::cout << "\nWould you like to\n1. View list\n2. Sort list\n3. View/Update show\n4. Add show\n5. Exit\n";
            std::cin >> response;
            clear();

            switch (response)
            {
            case 1:
            {
                std::cout << (std::string)showList;
                std::cin.ignore();

                break;
            }
            case 2:
            {
                int sortPrimary;
                int sortSecondary;
                bool descendingPrimary;
                bool descendingSecondary;

                std::cout << "\nWould you like to sort by:\n1. Name\n2. Score\n3. Episodes watched\n4. Episodes left\n5. None\n";
                std::cin >> sortPrimary;
                std::cout << "\n0. ascending\n1. Decending\n";
                std::cin >> descendingPrimary;

                std::cout << "\nWould you like to have a secondary sort by:\n1. Name\n2. Score\n3. Episodes watched\n4. Episodes left\n5. None\n";
                std::cin >> sortSecondary;
                std::cout << "\n0. ascending\n1. Decending\n";
                std::cin >> descendingSecondary;

                showList.sort(sortPrimary, sortSecondary, descendingPrimary, descendingSecondary);

                break;
            }
            case 3:
            {
                std::string name;
                bool cancel;

                if (!showList.hasShow())
                {
                    std::cout << "Your list is currently empty. Try adding some shows! ";
                    std::cin.ignore();
                    break;
                }

                std::cout << "Please enter the name of the show: ";
                std::cin >> name;

                name = showList.findShow(name);

                std::cout << "Confirm " << name << " is the show you are looking for\n0. Yes\n1. No\n";
                std::cin >> cancel;

                if (cancel)
                {
                    break;
                }

                Show &show = showList.getShow(name);
                int updateStatus;
                int newVal;
                while (true)
                {
                    clear();
                    std::cout << header() << "\n";
                    std::cout << "\n2. Watch episode\n2. Update score\n3. Update number of watched episodes\n4. Update the total number of episodes\n5. Exit\n";
                    std::cin >> updateStatus;

                    if (updateStatus == 5)
                    {
                        break;
                    }

                    if (updateStatus != 1 && updateStatus != 2 && updateStatus != 3 && updateStatus != 4)
                    {
                        throw std::exception();
                    }

                    if (updateStatus != 1)
                    {
                        std::cout << "\nPlease enter the updated value: ";
                        std::cin >> newVal;
                    }

                    if (updateStatus == 1)
                    {
                        show++;
                    }
                    else if (updateStatus == 2)
                    {
                        show.updateScore(newVal);
                    }
                    else if (updateStatus == 3)
                    {
                        show.updateWatched(newVal);
                    }
                    else
                    {
                        show.updateTotal(newVal);
                    }
                }

                break;
            }
            case 4:
            {
                std::string name;
                int score;
                int watched;
                int total;

                std::cout << "Enter the name: ";
                std::cin.ignore();

                while (trim(name) == "")
                {
                    std::getline(std::cin, name);
                }

                std::cout << "\nEnter your score (0 - 10): ";
                std::cin >> score;
                std::cout << "\nEnter the number of episodes you have watched: ";
                std::cin >> watched;
                std::cout << "\nEnter the total number of episodes: ";
                std::cin >> total;

                showList.addShow(name, score, watched, total);

                break;
            }
            case 5:
            {
                finished = true;
                break;
            }
            default:
                std::cout << "\nInvalid input. Press enter to continue\n";
                std::cin.ignore();
                break;
            }

            std::cin.ignore();
        }
        catch (std::exception e)
        {
            std::cout << "\nInvalid input. Please retry\n";
            std::cin.clear();
            std::cin.ignore();
        }
    }

    return 0;
}
