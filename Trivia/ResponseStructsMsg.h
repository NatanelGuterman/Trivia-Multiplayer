#pragma once
#include <iostream>
#include "json.hpp"
#include "EnumCodes.h"

typedef struct LoginResponse
{
	unsigned int _status;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginResponse, _status)


} LoginResponse;

typedef struct SignupResponse
{
	unsigned int _status;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(SignupResponse, _status)

} SignupResponse;


typedef struct ErrorResponse
{

	std::string _message;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ErrorResponse, _message)

}ErrorResponse;




