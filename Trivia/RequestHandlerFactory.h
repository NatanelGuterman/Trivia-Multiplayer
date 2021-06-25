#pragma once
#include "LoginRequestHandler.h"
#include "LoginManager.h"
#include "IDataBase.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();

private:

	IDataBase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	

};