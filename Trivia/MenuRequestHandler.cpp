#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler()
{
    //
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
    if (request.requestId >= LOGOUT_CODE && request.requestId <= CREATE_ROOM_CODE)
    {
        return true;
    }
    return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request)
{
    RequestResult requestResult;
    switch (request.requestId)
    {
    case LOGOUT_CODE:
    {
        requestResult = signout(request);
    }
    case GET_ROOM_CODE:
    {
        requestResult = getRooms(request);
    }
    case GET_PLAYERS_IN_ROOM_CODE:
    {
        requestResult = getPlayersInRoom(request);
    }
    case JOIN_ROOM_CODE:
    {
        requestResult = joinRoom(request);
    }
    case CREATE_ROOM_CODE:
    {
        requestResult = createRoom(request);
    }
    }
    return requestResult;
}

RequestResult MenuRequestHandler::signout(RequestInfo requestInfo)
{
    try {
        if (this->.signup())
        {
            return { JsonResponsePacketSerializer::serializeResponse(LoginResponse({OK_STATUS})), this->m_handlerFactory.createMenuRequestHandler() };
        }
        else
        {
            return { JsonResponsePacketSerializer::serializeResponse(LoginResponse({PROBLEM_STATUS})), this->m_handlerFactory.createLoginRequestHandler() };
        }
    }
    catch (std::exception& ex)
    {
        return { JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ERROR_MSG})), nullptr };
    }
}

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo)
{
    return RequestResult();
}
