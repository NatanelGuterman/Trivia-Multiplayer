#include "Server.h"

Server::Server()
{ 
	// Nothing To Do!
}

void Server::run()
{
	this->m_communicator.startHandleRequests();
}
