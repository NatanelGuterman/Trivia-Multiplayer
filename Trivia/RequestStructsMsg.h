#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include "IRequestHandler.h"
class IRequestHandler;
struct LoginRequest
{
	std::string username;
	std::string password;
} typedef LoginRequest;

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
} typedef SignupRequest;

struct RequestInfo
{
	int requestId;
	std::time_t receivalTime;
	std::vector<unsigned char> buffer;
} typedef RequestInfo;


struct RequestResult
{
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler;
} typedef RequestResult;

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
} typedef GetPlayersInRoomRequest;

struct JoinRoomRequest
{
	unsigned int roomId;
} typedef JoinRoomRequest;

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxUsers, questionCount, answerTimeout;
} typedef CreateRoomRequest;
