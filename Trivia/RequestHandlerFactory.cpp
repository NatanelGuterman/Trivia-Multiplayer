#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(this->m_loginManager, *this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser* user)
{
	return new MenuRequestHandler(*this, *user);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}
