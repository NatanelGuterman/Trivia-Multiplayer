#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user);
	virtual bool isRequestRelevant(RequestInfo request);
	virtual RequestResult handleRequest(RequestInfo request);
private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(RequestInfo requestInfo);
	RequestResult getRooms(RequestInfo requestInfo);
	RequestResult getPlayersInRoom(RequestInfo requestInfo);
	RequestResult joinRoom(RequestInfo requestInfo);
	RequestResult createRoom(RequestInfo requestInfo);
};
