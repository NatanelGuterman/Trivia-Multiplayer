#include "SqliteDataBase.h"
#include "sqlite3.h"

bool exists = false;
int callback_userExists(void* data, int argc, char** argv, char** azColName);

bool SqliteDataBase::doesUserExist(std::string username)
{
    std::string query = "", error = "";
    sqlQuery(SQL_BEGIN, SQL_BEGIN_ERROR, nullptr);

    query = "SELECT * FROM USERS WHERE Username=" + username + ";";
    error = "ERROR: doesUserExist() - Couldn't select from USERS.";

    sqlQuery(query.c_str(), error, callback_userExists);
    sqlQuery(SQL_COMMIT, SQL_COMMIT_ERROR, nullptr);

    return exists;
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

int callback_userExists(void* data, int argc, char** argv, char** azColName)
{
    exists = (argc == 0 ? false : true);
    return 0;
}