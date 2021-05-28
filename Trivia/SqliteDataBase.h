#pragma once
#include "IDataBase.h"

class SqliteDataBase : IDataBase
{
public:
	virtual bool doesUserExist(std::string username);
	virtual bool doesPasswordMatch(std::string password, std::string repeat);
	virtual void addNewUser(std::string username, std::string password, std::string mail);

};