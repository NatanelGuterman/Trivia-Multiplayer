#include "JsonRequestPacketDeserializer.h"
#include "LoginRequestHandler.h"
#include <bitset>

/*
*	Function will create a LoginRequest struct representation of the content that comes with the buffer
*	Input:
*		std::vector<unsigned char> buffer - a binary buffer to get all the fields (content) from after convert
*	Output:
*		LoginRequest -  a struct with the fields content from the buffer content
*/
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	int i = 0, j = 0;
	std::string dataLength = "", bytesData = "", tempCharacter = "", data = "";

	for (i = BYTE; i < BYTE * NUMBER_OF_DATA_BYTES; i++)
	{
		dataLength += buffer[i];
	}

	for (i = BYTE * NUMBER_OF_DATA_BYTES; i < stoi(dataLength, 0, BINARY); i++)
	{
		bytesData += buffer[i];
	}

	for (i = BYTE; i < stoi(dataLength, 0, BINARY) - BYTE; i += BYTE)
	{
		for (j = i; j < BYTE + i; j++)
		{
			tempCharacter += bytesData[j];
		}
		data += (char)std::stoi(tempCharacter, 0, BINARY);
		tempCharacter = "";
	}
	LoginRequest result = { data.substr(data.find(COLON) + ADD_FIND_USERNAME, data.find(COMMA) - data.find(COLON) - SUB_FIND_USERNAME), data.substr(data.find(COMMA) + ADD_FIND_PASSWORD, data.length() - data.find(COMMA) - SUB_FIND_PASSWORD) };
	return result;
}

/*
*	Function will create a SignupRequest struct representation of the content that comes with the buffer
*	Input:
*		std::vector<unsigned char> buffer - a binary buffer to get all the fields (content) from after convert
*	Output:
*		SignupRequest -  a struct with the fields content from the buffer content
*/
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(std::vector<unsigned char> buffer)
{
	int i = 0, j = 0;
	std::string dataLength = "", bytesData = "", tempCharacter = "", data = "";

	for (i = BYTE; i < BYTE * NUMBER_OF_DATA_BYTES; i++)
	{
		dataLength += buffer[i];
	}

	for (i = BYTE * NUMBER_OF_DATA_BYTES; i < stoi(dataLength, 0, BINARY); i++)
	{
		bytesData += buffer[i];
	}

	for (i = BYTE; i < stoi(dataLength, 0, BINARY); i += BYTE)
	{
		for (j = i; j < BYTE + i; j++)
		{
			tempCharacter += bytesData[j];
		}
		data += (char)std::stoi(tempCharacter, 0, BINARY);
		tempCharacter = "";
	}
	SignupRequest request = { data.substr(data.find(COLON) + ADD_FIND_USERNAME, data.find(COMMA) - data.find(COLON) - SUB_FIND_USERNAME), data.substr(data.find(COMMA) + ADD_FIND_PASSWORD, data.find(MAIL) - data.find(COMMA) - SUB_FIND_PASSWORD - 1), data.substr(data.find(MAIL) + FIND_MAIL, data.find(END_OF_JSON) - data.find(MAIL) - FIND_MAIL) };
	return request;
}
