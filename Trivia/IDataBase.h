#pragma once
#include <string>

class IDataBase
{
public:
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string password, std::string repeat) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string mail) = 0;

};
