#pragma once
#include "IDataBase.h"
#include "LoggedUser.h"
#include <vector>

class LoginManager
{
public:

private:
	IDataBase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};
