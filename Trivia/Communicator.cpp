#include "Communicator.h"


Communicator::Communicator()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP 
	this->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(this->m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	bindAndListen();
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	std::string msgServer = "";


	sa.sin_port = htons(MT_SERVER_PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(this->m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(this->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << MT_SERVER_PORT << std::endl;
	std::thread inputThread(&Communicator::waitingForServerInput, this, msgServer);
	inputThread.detach();
	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers


		std::cout << "Waiting for client connection request" << std::endl;
		accept();
	}
}

void Communicator::accept()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(this->m_serverSocket, NULL, NULL);

	if (this->_flagClosedSocket)
	{
		throw std::exception("Server Exited!");
	}

	if (client_socket == INVALID_SOCKET) {
		throw std::exception(__FUNCTION__);

	}

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	// the function that handle the conversation with the client
	addNewClientToMap(client_socket);
	std::thread clientThread(&Communicator::handleNewClient, this, client_socket);
	clientThread.detach();
}

void Communicator::handleNewClient(SOCKET socket)
{
	char* msgBuffer;
	msgBuffer = (char*)malloc(sizeof(char) * MIN_BUFFER_SIZE);
	int msgSize = 0;
	int i = 0;

	RequestInfo msgInfo = { 0, NULL, {'\0'} }; //initialize request info struct
	try
	{
		recv(socket, msgBuffer, MIN_BUFFER_SIZE - 1, 0); //recive from the client the buffer (request)
		msgBuffer[MIN_BUFFER_SIZE - 1] = 0; 
		msgInfo.requestId = std::stoi(std::string(msgBuffer).substr(0, BYTE_SIZE), 0, BINARY); //get the current message code
		msgSize = std::stoi(std::string(msgBuffer).substr(BYTE_SIZE, BYTE_SIZE * BYTE_MSG_SIZE), 0, BINARY); //get the current message size
		msgInfo.receivalTime = std::time(nullptr); //get the current time of the message recive
		msgBuffer = (char*)malloc(sizeof(char) * msgSize);
		recv(socket, msgBuffer, msgSize, 0); //get the rest part of the message (the json)
		for (i = 0; i < msgSize; i++)
		{
			std::cout << msgSize << std::endl;
			msgInfo.buffer.push_back(msgBuffer[i]);
		}
			
			
		if (this->m_clients[socket]->isRequestRelevant(msgInfo)) //check if the current request is valid 
		{
			RequestResult requestResult = this->m_clients[socket]->handleRequest(msgInfo); //call handle request to get the result of the operation
			send(socket, (char*)requestResult.buffer.data(), requestResult.buffer.size(), 0); //send the result buffer to the client
		}
		else //in case of the request isn't relevant
		{

			ErrorResponse errResponse{ ERROR_MSG };
			std::vector<unsigned char> errResponseBuffer = JsonResponsePacketSerializer::serializeResponse(errResponse); 
			send(socket, (char*)errResponseBuffer.data(), errResponseBuffer.size(), 0); //send error message to the client
		}
	}
	catch (const std::exception& e)
	{		
		// Closing the socket (in the level of the TCP protocol)
		closesocket(socket);
		free(msgBuffer);
	}
}
//
void Communicator::addNewClientToMap(SOCKET socket)
{
	LoginRequestHandler* loginRequestHandlerInstance = new LoginRequestHandler();
	this->m_clients[socket] = loginRequestHandlerInstance;
}


void Communicator::waitingForServerInput(std::string msgServer)
{
	while (msgServer != EXIT_MSG)
	{
		std::getline(std::cin, msgServer);
	}
	closesocket(this->m_serverSocket);
	_flagClosedSocket = true;
}