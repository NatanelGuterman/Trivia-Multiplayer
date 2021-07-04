#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser& user) : m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager()), m_user(user)
{

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
        break;
    }
    case GET_ROOM_CODE:
    {
        requestResult = getRooms(request);
        break;
    }
    case GET_PLAYERS_IN_ROOM_CODE:
    {
        requestResult = getPlayersInRoom(request);
        break;
    }
    case JOIN_ROOM_CODE:
    {
        requestResult = joinRoom(request);
        break;
    }
    case CREATE_ROOM_CODE:
    {
        requestResult = createRoom(request);
        break;
    }
    }
    return requestResult;
}

RequestResult MenuRequestHandler::signout(RequestInfo requestInfo)
{
    try {
        if (this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername()))
        {
            return { JsonResponsePacketSerializer::serializeResponse(LogoutResponse({OK_STATUS})), this };
        }
        else
        {
            return { JsonResponsePacketSerializer::serializeResponse(LogoutResponse({PROBLEM_STATUS})), nullptr };
        }
    }
    catch (std::exception& ex)
    {
        return { JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ERROR_MSG})), nullptr };
    }
}

RequestResult MenuRequestHandler::getRooms(RequestInfo requestInfo)
{
    try {
        return { JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse({OK_STATUS, this->m_roomManager.getRoomsData()})), this };
    }
    catch (std::exception& ex)
    {
        return { JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ERROR_MSG})), nullptr };
    }
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo)
{
    try {
        GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(requestInfo.buffer);
        return { JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse({this->m_roomManager.getRoomsMap()[getPlayersInRoomRequest.roomId].getAllUsers()})), this };

    }
    catch (std::exception& ex)
    {
        return { JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ERROR_MSG})), nullptr };
    }
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo requestInfo)
{
    try {
        JoinRoomRequest joinRoomRequest =  JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
        this->m_handlerFactory.getRoomManager().addUser(joinRoomRequest.roomId, this->m_user);
        return { JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse({OK_STATUS})), this};
    }
    catch (std::exception& ex)
    {
        return { JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ERROR_MSG})), nullptr };
    }
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo)
{
    try {
        CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);
        this->m_handlerFactory.getRoomManager().createRoom(this->m_user, RoomData({this->m_roomManager.generateRoomId(), createRoomRequest.maxUsers, createRoomRequest.questionCount, createRoomRequest.answerTimeout, 0,  createRoomRequest.roomName}));
        return { JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse({OK_STATUS})), this };

    }
    catch (std::exception& ex)
    {
        return { JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ERROR_MSG})), nullptr };
    }
}
