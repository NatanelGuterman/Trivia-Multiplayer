#pragma once
#include <WinSock2.h>
#include <map>
#include "IRequestHandler.h"
#include <iostream>
#include <thread>

#define MT_SERVER_PORT 2620

class Communicator
{
public:
	Communicator();
	~Communicator();

	void startHandleRequests();

private:
	// Fields
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;

	// Methods
	void bindAndListen();
	void accept();
	void handleNewClient(SOCKET socket);

};
