#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
    if (request.requestId == LOGIN_CODE || request.requestId == SIGNUP_CODE)
    {
        return true;
    }
    return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
    RequestResult requestResult;
    if (request.requestId == LOGIN_CODE)
    {
        //JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
        requestResult = { JsonResponsePacketSerializer::serializeResponse(LoginResponse({OK_STATUS})), nullptr};
    }
    else
    {
        //JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
        requestResult = { JsonResponsePacketSerializer::serializeResponse(SignupResponse({OK_STATUS})), nullptr };
    }
    return requestResult;
}
