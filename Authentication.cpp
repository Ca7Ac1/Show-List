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

    File userInfo = File(kAuthenticationFile);

    while (!userInfo.end())
    {
        std::string readUsername = userInfo.readNext();
        std::string readPassword = userInfo.readNext();
        userInfo.skipLine();
        
        if (readUsername == username)
        {
            return password == readPassword;
        }
    }

    userInfo.writeLine(username + " " + password);

    return true;
}
