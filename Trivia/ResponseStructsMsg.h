#pragma once
#include <iostream>

typedef struct LoginResponse
{
	unsigned int _status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int _status;
} SignupResponse;

typedef struct ErrorResponse
{
	std::string _message;
}ErrorResponse;