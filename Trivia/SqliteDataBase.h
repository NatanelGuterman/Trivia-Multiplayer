#pragma once
#include "IDataBase.h"
#include <iostream>

class SqliteDataBase : IDataBase
{
public:
	virtual bool doesUserExist(std::string username);
	virtual bool doesPasswordMatch(std::string password, std::string repeat);
	virtual void addNewUser(std::string username, std::string password, std::string mail);

private:
	sqlite3* _Database;
	void sqlQuery(const char* query, std::string error, int (*ptr)(void*, int, char**, char**)); // Helper Method

};