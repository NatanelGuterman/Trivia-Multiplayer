#include "Server.h"

Server::Server(IDataBase* dataBase) : m_communicator(this->m_handlerFactory), m_database(dataBase)
{ 
	
}

Server::~Server()
{
}

void Server::run()
{
	this->m_communicator.startHandleRequests();
}
