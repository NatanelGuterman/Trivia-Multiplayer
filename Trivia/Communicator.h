#pragma once
#include <WinSock2.h>
#include <map>
#include "LoginRequestHandler.h"
#include <iostream>
#include <thread>
#include <string>



#define MT_SERVER_PORT 2620
#define HELLO_MSG_SIZE 6
#define EXIT_MSG "EXIT"

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
	bool _flagClosedSocket;


	// Methods
	void bindAndListen();
	void accept();
	void handleNewClient(SOCKET socket);
	void addNewClientToMap(SOCKET socket);
	void waitingForServerInput(std::string msgServer);

};
