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
        sqlQuery("CREATE TABLE USERS (Username TEXT PRIMARY KEY NOT NULL, Password TEXT NOT NULL, Mail TEXT NOT NULL);", "ERROR: open() - Couldn't create table USERS.", nullptr); // table USERS
        sqlQuery("CREATE TABLE QUESTIONS (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, Question TEXT NOT NULL, RightAns TEXT NOT NULL, WrongAns1 TEXT NOT NULL, WrongAns2 TEXT NOT NULL, WrongAns3 TEXT NOT NULL);", "ERROR: open() - Couldn't create table QUESTIONS.", nullptr); // table QUESTIONS
        addQuestionToDB("What does CPU stand for?", "Central Processing Unit", "Central Process Unit", "Computer Personal Unit", "Central Processor Unit");
        addQuestionToDB("According to the International System of Units, how many bytes are in a kilobyte of RAM?", "1000", "512", "1024", "500");
        addQuestionToDB("On which day did the World Wide Web go online?", "December 20, 1990", "December 17, 1996", "November 12, 1990", "November 24, 1995");
        addQuestionToDB("What was the name given to Android 4.3?", "Jelly Bean", "Lollipop", "Nutella", "Froyo");
        addQuestionToDB("In web design, what does CSS stand for?", "Cascading Style Sheet", "Counter Strike: Source", "Corrective Style Sheet", "Computer Style Sheet");
        addQuestionToDB("In computing terms, typically what does CLI stand for?", "Command Line Interface", "Common Language Input", "Control Line Interface", "Common Language Interface");
        addQuestionToDB("Which operating system was released first?", "Mac OS", "Windows", "Linux", "OS\/2");
        addQuestionToDB("What does the term MIME stand for, in regards to computing?", "Multipurpose Internet Mail Extensions", "Mail Internet Mail Exchange", "Multipurpose Interleave Mail Exchange", "Mail Interleave Method Exchange");
        addQuestionToDB("Which programming language was developed by Sun Microsystems in 1995?", "Java", "Python", "Solaris OS", "C++");
        addQuestionToDB("In computing, what does LAN stand for?", "Local Area Network", "Long Antenna Node", "Light Access Node", "Land Address Navigation");
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

void SqliteDataBase::addQuestionToDB(std::string question, std::string rightAns, std::string wrongAns1, std::string wrongAns2, std::string wrondAns3)
{
    std::string query = "", error = "";
    sqlQuery(SQL_BEGIN, SQL_BEGIN_ERROR, nullptr);

    query = "INSERT INTO QUESTIONS (Question, RightAns, WrongAns1, WrongAns2, WrongAns3) VALUES(\"" + question + "\", \"" + rightAns + "\", \"" + wrongAns1 + "\", \"" + wrongAns2 + "\", \"" + wrondAns3 + "\");";
    error = "ERROR: addQuestionToDB() - Couldn't insert into QUESTIONS.";

    sqlQuery(query.c_str(), error, nullptr);
    sqlQuery(SQL_COMMIT, SQL_COMMIT_ERROR, nullptr);
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