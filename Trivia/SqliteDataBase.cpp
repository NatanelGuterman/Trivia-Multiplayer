#include "SqliteDataBase.h"
#include "sqlite3.h"

bool SqliteDataBase::doesUserExist(std::string username)
{
    return false;
}

bool SqliteDataBase::doesPasswordMatch(std::string password, std::string repeat)
{
    return false;
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string mail)
{
}

// Helper mehtod.
void SqliteDataBase::sqlQuery(const char* query, std::string error, int(*ptr)(void*, int, char**, char**))
{
    char* errMessage = nullptr;
    int res = sqlite3_exec(this->_Database, query, ptr, nullptr, &errMessage);
    if (res != SQLITE_OK)
    {
        std::cerr << error << std::endl << errMessage << std::endl << std::endl;
    }
}
