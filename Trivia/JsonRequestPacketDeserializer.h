#pragma once
#include "RequestStructsMsg.h"
#include <string>
#include <bitset>

#define BYTE 8
#define NUMBER_OF_DATA_BYTES 4
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
