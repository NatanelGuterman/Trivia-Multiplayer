#pragma once
#include <WinSock2.h>
#include <map>
#include "IRequestHandler.h"

class Communicator
{
public:
	void startHandleRequests();

private:
	// Fields
	SOCKET m_serverSicket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	// Methods
	void bindAndListen();
	void handleNewClient(SOCKET socket);

};
