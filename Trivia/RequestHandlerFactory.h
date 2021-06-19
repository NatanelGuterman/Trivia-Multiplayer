#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "IDataBase.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();

private:

	IDataBase* m_database;
	LoginManager m_loginManager;

};