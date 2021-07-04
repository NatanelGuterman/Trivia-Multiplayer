#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory): m_loginManager(loginManager), m_handlerFactory(handlerFactory)
{
}

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
        requestResult = login(request);
    }
    else
    {
        requestResult = signup(request);
    }
    return requestResult;
}

RequestResult LoginRequestHandler::login(RequestInfo request)
{
    try {
        LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
        if (this->m_loginManager.login(loginRequest.username, loginRequest.password))
        {
            return { JsonResponsePacketSerializer::serializeResponse(LoginResponse({OK_STATUS})), this->m_handlerFactory.createMenuRequestHandler(new LoggedUser(loginRequest.username)) };
        }
        else
        {
            return { JsonResponsePacketSerializer::serializeResponse(LoginResponse({PROBLEM_STATUS})), this->m_handlerFactory.createLoginRequestHandler() };
        }
    }
    catch(std::exception& ex)
    {
        return { JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ERROR_MSG})), nullptr };
    }


}

RequestResult LoginRequestHandler::signup(RequestInfo request)
{
    try {
        SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
        if (this->m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.email))
        {
            return { JsonResponsePacketSerializer::serializeResponse(SignupResponse({OK_STATUS})), this->m_handlerFactory.createMenuRequestHandler(new LoggedUser(signupRequest.username)) };
        }
        else
        {
            return { JsonResponsePacketSerializer::serializeResponse(SignupResponse({PROBLEM_STATUS})), this->m_handlerFactory.createLoginRequestHandler() };
        }
    }
    catch (std::exception& ex)
    {
        return { JsonResponsePacketSerializer::serializeResponse(ErrorResponse({ERROR_MSG})), nullptr };
    }
}
