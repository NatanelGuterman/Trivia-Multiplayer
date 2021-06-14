#pragma once
#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include <vector>

class LoginManager
{
public:
	void signup(std::string username, std::string password, std::string mail);
	void login(std::string username, std::string password);
	void logout(std::string username);

private:
	SqliteDataBase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
