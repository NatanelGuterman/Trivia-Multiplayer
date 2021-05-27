#pragma once
#include "RequestStructsMsg.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	static bool isRequestRelevant(RequestInfo request);
	static RequestResult handleRequest(RequestInfo request);

};
