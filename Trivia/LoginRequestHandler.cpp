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
    return RequestResult();
}
