#include "Authentication.h"
#include "Formatting.h"
#include "File.h"

#include <string>

bool authenticate(const std::string &username, const std::string &password)
{
    if (username.find(" ") != std::string::npos || password.find(" ") != std::string::npos || trim(username) == "" || trim(password) == "")
    {
        return false;
    }

    FileReader userInfoReader(kAuthenticationFile);

    while (!userInfoReader.isEnd())
    {
        std::string readUsername = trim(userInfoReader.readNext());
        std::string readPassword = trim(userInfoReader.readNext());
        userInfoReader.skipLine();

        if (readUsername == username)
        {
            return password == readPassword;
        }
    }

    FileWriter userInfoWriter(kAuthenticationFile);
    userInfoWriter.writeLine(username + " " + password);

    return true;
}
