#include "JsonRequestPacketDeserializer.h"
#include "LoginRequestHandler.h"
#include <bitset>

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	int i = 0, j = 0;
	std::string dataLength = "", bytesData = "", tempCharacter = "", data = "";

	for (i = BYTE; i < BYTE * NUMBER_OF_DATA_BYTES; i++)
	{
		dataLength += buffer[i];
	}

	for (i = BYTE * NUMBER_OF_DATA_BYTES; i < stoi(dataLength, 0, 2); i++)
	{
		bytesData += buffer[i];
	}

	for (i = BYTE; i < stoi(dataLength, 0, 2) - BYTE; i += BYTE)
	{
		for (j = i; j < BYTE + i; j++)
		{
			tempCharacter += bytesData[j];
		}
		data += (char)std::stoi(tempCharacter, 0, 2);
		tempCharacter = "";
	}
	LoginRequest result = { data.substr(data.find(":") + ADD_FIND_USERNAME, data.find(",") - data.find(":") - SUB_FIND_USERNAME), data.substr(data.find(",") + ADD_FIND_PASSWORD, data.length() - data.find(",") - SUB_FIND_PASSWORD) };
	return result;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	int i = 0, j = 0;
	std::string dataLength = "", bytesData = "", tempCharacter = "", data = "";

	for (i = BYTE; i < BYTE * NUMBER_OF_DATA_BYTES; i++)
	{
		dataLength += buffer[i];
	}

	for (i = BYTE * NUMBER_OF_DATA_BYTES; i < stoi(dataLength, 0, 2); i++)
	{
		bytesData += buffer[i];
	}

	for (i = BYTE; i < stoi(dataLength, 0, 2); i += BYTE)
	{
		for (j = i; j < BYTE + i; j++)
		{
			tempCharacter += bytesData[j];
		}
		data += (char)std::stoi(tempCharacter, 0, 2);
		tempCharacter = "";
	}
	SignupRequest request = { data.substr(data.find(":") + ADD_FIND_USERNAME, data.find(",") - data.find(":") - SUB_FIND_USERNAME), data.substr(data.find(",") + ADD_FIND_PASSWORD, data.find(MAIL) - data.find(COMMA) - SUB_FIND_PASSWORD - 1), data.substr(data.find(MAIL) + FIND_MAIL, data.find(END_OF_JSON) - data.find(MAIL) - FIND_MAIL) };
	return request;
}
