#pragma once
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include <vector>

class LoginManager
{
public:
	LoginManager();
	bool signup(std::string username, std::string password, std::string mail);
	bool login(std::string username, std::string password);
	bool logout(std::string username);

private:
	SqliteDataBase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
