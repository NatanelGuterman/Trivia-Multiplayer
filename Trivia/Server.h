#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "IDataBase.h"


class Server
{
public:
	Server(IDataBase* dataBase);
	~Server();

	void run();

private:
	Communicator m_communicator;
	IDataBase* m_database;
	RequestHandlerFactory m_handlerFactory;

};
