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
	try
	{
		std::string welcomeString = "Hello";
		send(socket, welcomeString.c_str(), welcomeString.size(), 0);  // last parameter: flag. for us will be 0.

		char msgBuffer[HELLO_MSG_SIZE];
		recv(socket, msgBuffer, 5, 0);
		msgBuffer[5] = 0;
		std::cout << "Message from client: " << msgBuffer << std::endl;
		// Closing the socket (in the level of the TCP protocol)
	}
	catch (const std::exception& e)
	{
		closesocket(socket);

	}
}

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