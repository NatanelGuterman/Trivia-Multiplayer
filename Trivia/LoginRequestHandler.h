#pragma once
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"
#include <exception>

#define OK_STATUS 1
#define PROBLEM_STATUS 0

#define ERROR_MSG "ERROR"

class RequestHandlerFactory;

class LoginRequestHandler: public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo request);
	virtual RequestResult handleRequest(RequestInfo request);

private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult login(RequestInfo request);
	RequestResult signup(RequestInfo request);

};
