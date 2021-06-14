#pragma once
#include <vector>
#include <iostream>
#include <bitset>
#include <algorithm>
#include "ResponseStructsMsg.h"

#define ERASE_UNDERSCORE erase(1, 2) //earse underscore from json string representation
#define BYTE_SIZE 8
#define AMOUNT_OF_BYTES 4

class JsonResponsePacketSerializer
{
public:
	static std::vector<unsigned char> serializeResponse(ErrorResponse errResponse);
	static std::vector<unsigned char> serializeResponse(LoginResponse loginResponse);
	static std::vector<unsigned char> serializeResponse(SignupResponse SignupResponse);
private:
	static std::string turnStringIntoBinary(std::string stringToBin);
	static std::string removeUnneededCharacters(std::string stringToClean);
	static std::vector<unsigned char> createBufferFromJson(nlohmann::json ResponseJson, int codeResponse);



};

