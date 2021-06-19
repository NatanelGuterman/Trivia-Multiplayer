#include "SqliteDataBase.h"
#include "sqlite3.h"

bool flag = false;
std::string temp = "";

int callback_userExists(void* data, int argc, char** argv, char** azColName);
int callback_passwordMatch(void* data, int argc, char** argv, char** azColName);

bool SqliteDataBase::open()
{
    std::string dbFileName = "TriviaDB.db";
    int doesFileExist = _access(dbFileName.c_str(), 0);

    int res = sqlite3_open(dbFileName.c_str(), &this->_Database);
    if (res != SQLITE_OK)
    {
        this->_Database = nullptr;
        std::cout << "Failed to open Database." << std::endl;
        return false;
    }

    if (doesFileExist == -1)
    {
        std::cout << "Creating tables..." << std::endl;
        sqlQuery("CREATE TABLE USERS (Username TEXT PRIMARY KEY NOT NULL, Password TEXT NOT NULL, Mail TEXT NOT NULL);", "ERROR: open() - Couldn't create table USERS.", nullptr);
        std::cout << "Finished!" << std::endl;
    }

    return true;
}

void SqliteDataBase::close()
{
    sqlite3_close(this->_Database);
    this->_Database = nullptr;
}

void SqliteDataBase::clear()
{
    sqlQuery("DROP TABLE USERS", "ERROR: clear() - Could't drop table USERS.", nullptr);
    delete this->_Database;
}

SqliteDataBase::SqliteDataBase()
{
    open();
}

SqliteDataBase::~SqliteDataBase()
{
    close();
}


/*
This function checks if the user exists by it's username.
input: std::string username --> The username.
output: bool flag --> true if exists, false if not.
*/
bool SqliteDataBase::doesUserExist(std::string username)
{
    std::string query = "", error = "";
    sqlQuery(SQL_BEGIN, SQL_BEGIN_ERROR, nullptr);

    query = "SELECT * FROM USERS WHERE Username=\"" + username + "\";";
    error = "ERROR: doesUserExist() - Couldn't select from USERS.";

    sqlQuery(query.c_str(), error, callback_userExists);
    sqlQuery(SQL_COMMIT, SQL_COMMIT_ERROR, nullptr);

    return flag;
}

/*
This function checks if the password matches the username.
input: std::string username --> The username.
       std::string password --> The password.
output: bool flag --> true if exists, false if not.
*/

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
    std::string query = "", error = "";
    sqlQuery(SQL_BEGIN, SQL_BEGIN_ERROR, nullptr);

    query = "SELECT Password FROM USERS WHERE Username=\"" + username + "\";";
    error = "ERROR: doesPasswordMatch() - Couldn't select from USERS.";

    sqlQuery(query.c_str(), error, callback_passwordMatch);
    sqlQuery(SQL_COMMIT, SQL_COMMIT_ERROR, nullptr);

    return password == temp;
}

/*
This function adds a new user to the DB.
input: std::string username --> The username.
       std::string password --> The password.
       std::string mail --> The mail address.
output: None.
*/

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string mail)
{
    std::string query = "", error = "";
    sqlQuery(SQL_BEGIN, SQL_BEGIN_ERROR, nullptr);

    query = "INSERT INTO USERS (Username, Password, Mail) VALUES(\"" + username + "\", \"" + password + "\", \"" + mail + "\");";
    error = "ERROR: addNewUser() - Couldn't insert into USERS.";

    sqlQuery(query.c_str(), error, nullptr);
    sqlQuery(SQL_COMMIT, SQL_COMMIT_ERROR, nullptr);
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

// CALLBACK FUNCTIONS
int callback_userExists(void* data, int argc, char** argv, char** azColName)
{
    flag = (argc == 0 ? false : true);
    return 0;
}

int callback_passwordMatch(void* data, int argc, char** argv, char** azColName)
{
    temp = (argc == 1 ? azColName[1] : "");
    return 0;
}