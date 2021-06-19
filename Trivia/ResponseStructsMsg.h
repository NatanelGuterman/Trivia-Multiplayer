#pragma once
#include <iostream>
#include "json.hpp"
#include "EnumCodes.h"
#include "Room.h"

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

typedef struct LogoutResponse
{

	unsigned int _status;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(LogoutResponse, _status)

}LogoutResponse;

typedef struct GetRoomsResponse
{

	unsigned int _status;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetRoomsResponse, _status)
	std::vector<RoomData> _rooms; //!

}GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	std::vector<std::string> _players;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetPlayersInRoomResponse, _players)

}GetPlayersInRoomResponse;

typedef struct JoinRoomResponse
{

	unsigned int _status;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(JoinRoomResponse, _status)

}JoinRoomResponse;

typedef struct CreateRoomResponse
{

	unsigned int _status;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CreateRoomResponse, _status)

}CreateRoomResponse;







