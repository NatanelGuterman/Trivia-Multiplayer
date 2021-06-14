#pragma once
#include "RequestStructsMsg.h"
#include <string>
#include <bitset>

#define BYTE 8
#define NUMBER_OF_DATA_BYTES 4
#define ADD_FIND_USERNAME 2
#define SUB_FIND_USERNAME 3
#define ADD_FIND_PASSWORD 11
#define SUB_FIND_PASSWORD 12
#define MAIL "mail"
#define FIND_MAIL 5
#define COMMA ","
#define END_OF_JSON "}"
#define COLON ":"
#define BINARY 2

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned  char> buffer);
	static SignupRequest deserializeSignupRequest(std::vector<unsigned  char> buffer);

};
