#include "LoginRequestHandler.h"

std::string JsonRequestPacketDeserializer::getData(std::vector<unsigned char> buffer)
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

	return data;
}

/*
*	Function will create a LoginRequest struct representation of the content that comes with the buffer
*	Input:
*		std::vector<unsigned char> buffer - a binary buffer to get all the fields (content) from after convert
*	Output:
*		LoginRequest -  a struct with the fields content from the buffer content
*/

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer)
{
	std::string data = getData(buffer);
	LoginRequest result;

	nlohmann::json jsonResult = nlohmann::json::parse(data); // Parse string in json format to json object
	// Fill request fields with the json values
	result.username = jsonResult["username"];
	result.password = jsonResult["password"];
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
	std::string data = getData(buffer);
	SignupRequest result;

	nlohmann::json jsonResult = nlohmann::json::parse(data); // Parse string in json format to json object
	// Fill request fields with the json values
	result.username = jsonResult["username"];
	result.password = jsonResult["password"];
	result.email = jsonResult["mail"];
	return result;
}

/*
This function will create a GetPlayersInRoomRequest struct representation of the content that comes with the buffer.
input: std::vector<unsigned char> buffer --> a binary buffer to get all the fields (content) from after convert.
output: GetPlayersInRoomRequest result --> a struct with the fields content from the buffer content.
*/

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(std::vector<unsigned char> buffer)
{
	std::string data = getData(buffer);
	GetPlayersInRoomRequest result;

	nlohmann::json jsonResult = nlohmann::json::parse(data); // Parse string in json format to json object
	// Fill request fields with the json values
	result.roomId = jsonResult["roomId"];
	return result;
}

/*
This function will create a JoinRoomRequest struct representation of the content that comes with the buffer.
input: std::vector<unsigned char> buffer --> a binary buffer to get all the fields (content) from after convert.
output: JoinRoomRequest result --> a struct with the fields content from the buffer content.
*/

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<unsigned char> buffer)
{
	std::string data = getData(buffer);
	JoinRoomRequest result;

	nlohmann::json jsonResult = nlohmann::json::parse(data); // Parse string in json format to json object
	// Fill request fields with the json values
	result.roomId = jsonResult["roomId"];
	return result;
}

/*
This function will create a CreateRoomRequest struct representation of the content that comes with the buffer.
input: std::vector<unsigned char> buffer --> a binary buffer to get all the fields (content) from after convert.
output: CreateRoomRequest result --> a struct with the fields content from the buffer content.
*/

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<unsigned char> buffer)
{
	std::string data = getData(buffer);
	CreateRoomRequest result;

	nlohmann::json jsonResult = nlohmann::json::parse(data); // Parse string in json format to json object
	// Fill request fields with the json values
	result.roomName = jsonResult["roomName"];
	result.maxUsers = jsonResult["maxUsers"];
	result.questionCount = jsonResult["questionCount"];
	result.answerTimeout = jsonResult["answerTimeout"];
	return result;
}
