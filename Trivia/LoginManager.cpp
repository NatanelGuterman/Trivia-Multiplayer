#include "LoginManager.h"

/*
This function sings up a user (adding to the DB).
input: std::string username --> The username.
	   std::string password --> The password.
	   std::string mail --> The mail address.
output: None.
*/

void LoginManager::signup(std::string username, std::string password, std::string mail)
{
	this->m_database->addNewUser(username, password, mail);
}

/*
This function logs a user (adding to the logged user vector).
input: std::string username --> The username.
	   std::string password --> The password.
output: None.
*/

void LoginManager::login(std::string username, std::string password)
{
	if (this->m_database->doesUserExist(username) && this->m_database->doesPasswordMatch(username, password))
	{
		this->m_loggedUsers.push_back(LoggedUser(username));
	}
}

/*
This function logs out a user (removing from the logged user vector).
input: std::string username --> The username.
output: None.
*/

void LoginManager::logout(std::string username)
{
	std::vector<LoggedUser>::iterator iter = this->m_loggedUsers.begin();

	while (iter != this->m_loggedUsers.end())
	{
		if ((*iter).getUsername() == username)
		{
			this->m_loggedUsers.erase(iter);
		}
	}
}
