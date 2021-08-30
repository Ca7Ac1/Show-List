#include "Authentication.h"
#include "Formatting.h"

#include <string>


bool authenticate(const std::string &username, const std::string &password)
{
    if (trim(username) == "" || trim(password) == "")
    {
        return false;
    }
    
    return true;
}
