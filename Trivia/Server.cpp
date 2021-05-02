#include "Server.h"

Server::Server()
{ 
	// Nothing To Do!
}

Server::~Server()
{
}

void Server::run()
{
	this->m_communicator.startHandleRequests();
}
