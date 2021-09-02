#include "Authentication.h"
#include "Formatting.h"
#include "File.h"

#include <string>


bool authenticate(const std::string &username, const std::string &password)
{
    if (trim(username) == "" || trim(password) == "")
    {
        return false;
    }

    FileReader userInfoReader = FileReader(kAuthenticationFile);

    while (!userInfoReader.isEnd())
    {
        std::string readUsername = userInfoReader.readNext();
        std::string readPassword = userInfoReader.readNext();
        userInfoReader.skipLine();
        
        if (readUsername == username)
        {
            return password == readPassword;
        }
    }

    FileWriter userInfoWriter = FileWriter(kAuthenticationFile);
    userInfoWriter.writeLine(username + " " + password);

    return true;
}
