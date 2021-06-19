#pragma once
#include "IDataBase.h"
#include <iostream>
#include "sqlite3.h"
#include <io.h>

#define SQL_BEGIN "BEGIN;"
#define SQL_COMMIT "COMMIT;"
#define SQL_BEGIN_ERROR "Couldn't send BEGIN."
#define SQL_COMMIT_ERROR "Couldn't send COMMIT."


class SqliteDataBase : public IDataBase
{
public:
	SqliteDataBase();
	~SqliteDataBase();
	virtual bool doesUserExist(std::string username);
	virtual bool doesPasswordMatch(std::string username, std::string password);
	virtual void addNewUser(std::string username, std::string password, std::string mail);

	virtual bool open() override;
	virtual void close() override;
	virtual void clear() override;

private:
	sqlite3* _Database;
	void sqlQuery(const char* query, std::string error, int (*ptr)(void*, int, char**, char**)); // Helper Method

};