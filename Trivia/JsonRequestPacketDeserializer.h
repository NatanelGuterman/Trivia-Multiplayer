#pragma once
#include "RequestStructsMsg.h"
#include <string>
#include <bitset>

#define BYTE 8
#define NUMBER_OF_DATA_BYTES 4
#define ADD_FIND_USERNAME 3
#define SUB_FIND_USERNAME 3
#define ADD_FIND_PASSWORD 15
#define SUB_FIND_PASSWORD 15
#define END_AFTER_LAST_VALUE 2
#define END_AFTER_LAST_VALUE_MAIL 4
#define MAIL "mail"
#define FIND_MAIL 8
#define COMMA ","
#define END_OF_JSON "}"
#define COLON ":"
#define BINARY 2

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned char> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(std::vector<unsigned char> buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<unsigned char> buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<unsigned char> buffer);

private:
	static std::string getData(std::vector<unsigned char> buffer);
};
