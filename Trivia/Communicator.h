#pragma once
#include <WinSock2.h>
#include <map>
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include <iostream>
#include <thread>
#include <string>
#include <vector>



#define MT_SERVER_PORT 2620
#define EXIT_MSG "EXIT"
#define MIN_BUFFER_SIZE 41
#define BINARY 2
#define BYTE_SIZE 8
#define BYTE_MSG_SIZE 4

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
