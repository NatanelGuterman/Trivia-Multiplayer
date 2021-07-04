#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "IDataBase.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser* user);
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();

private:

	IDataBase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	

};