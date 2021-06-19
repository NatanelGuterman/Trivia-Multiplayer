#include "LoginRequestHandler.h"

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
	std::string bytesData = "", tempCharacter = "", data = "";

	for (i = 1; i < buffer.size(); i++)
	{
		bytesData += buffer[i];
	}

	for (i = 0; i < buffer.size() - 1; i += BYTE)
	{
		for (j = i; j < BYTE + i; j++)
		{
			tempCharacter += bytesData[j];
		}
		data += (char)std::stoi(tempCharacter, 0, BINARY);
		tempCharacter = "";
	}
	LoginRequest result = { data.substr(data.find(COLON) + ADD_FIND_USERNAME, (data.find(COMMA) - 1) - data.find(COLON) - SUB_FIND_USERNAME), data.substr(data.find(COMMA) + ADD_FIND_PASSWORD, (data.length() - END_AFTER_LAST_VALUE) - (data.find(COMMA) + SUB_FIND_PASSWORD))};
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
	std::string bytesData = "", tempCharacter = "", data = "";

	for (i = 1; i < buffer.size(); i++)
	{
		bytesData += buffer[i];
	}

	for (i = 0; i < buffer.size() - 1; i += BYTE)
	{
		for (j = i; j < BYTE + i; j++)
		{
			tempCharacter += bytesData[j];
		}
		data += (char)std::stoi(tempCharacter, 0, BINARY);
		tempCharacter = "";
	}
	SignupRequest request = { data.substr(data.find(COLON) + ADD_FIND_USERNAME, (data.find(COMMA) - 1) - data.find(COLON) - SUB_FIND_USERNAME), data.substr(data.find(COMMA) + ADD_FIND_PASSWORD, data.find(MAIL) - END_AFTER_LAST_VALUE_MAIL - (data.find(COMMA) + SUB_FIND_PASSWORD)), data.substr(data.find(MAIL) + FIND_MAIL, data.find(END_OF_JSON) - 1 - (data.find(MAIL) + FIND_MAIL)) };
	return request;
}
