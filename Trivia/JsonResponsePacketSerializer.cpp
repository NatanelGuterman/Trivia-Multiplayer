#include "JsonResponsePacketSerializer.h"

/*
*   Function will get a reponse struct and return a binary buffer representation
*   Input:
*       ErrorResponse errResponse - sturct to get it's attributes into buffer
*   Output:
*       std::vector<unsigned char> - a buffer (binary) to send to client
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse errResponse)
{
    nlohmann::json errorResponseJson = errResponse;
    return createBufferFromJson(errorResponseJson, ERROR_CODE);
}

/*
*   Function will get a reponse struct and return a binary buffer representation
*   Input:
*       ErrorResponse loginResponse - sturct to get it's attributes into buffer
*   Output:
*       std::vector<unsigned char> - a buffer (binary) to send to client
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse)
{
    nlohmann::json loginResponseJson = loginResponse;
    return createBufferFromJson(loginResponseJson, LOGIN_CODE);
}

/*
*   Function will get a reponse struct and return a binary buffer representation
*   Input:
*       ErrorResponse SignupResponse - sturct to get it's attributes into buffer
*   Output:
*       std::vector<unsigned char> - a buffer (binary) to send to client
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse SignupResponse)
{
    nlohmann::json signupResponseJson = SignupResponse;
    return createBufferFromJson(signupResponseJson, SIGNUP_CODE);
}

/*
*   Function will get a response struct and return a binary buffer representation
*   Input:
*       LogoutResponse logoutResponse - sturct to get it's attributes into buffer
*   Output:
*       std::vector<unsigned char> - a buffer (binary) to send to client
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutResponse)
{
    nlohmann::json logoutResponseJson = logoutResponse;
    return createBufferFromJson(logoutResponseJson, LOGOUT_CODE);
}

/*
*   Function will get a response struct and return a binary buffer representation
*   Input:
*       GetRoomsResponse getRoomsResponse - sturct to get it's attributes into buffer
*   Output:
*       std::vector<unsigned char> - a buffer (binary) to send to client
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRoomsResponse)
{
    nlohmann::json getRoomsResponseJson;
    int i = 0;

    for (i = 0; i < getRoomsResponse._rooms.size(); i++)
    {
        getRoomsResponseJson["Rooms"]["room" + std::to_string(i + 1)]["id"] = getRoomsResponse._rooms[i].id;
        getRoomsResponseJson["Rooms"]["room" + std::to_string(i + 1)]["maxPlayers"] = getRoomsResponse._rooms[i].maxPlayers;
        getRoomsResponseJson["Rooms"]["room" + std::to_string(i + 1)]["numOfQuestionsInGame"] = getRoomsResponse._rooms[i].numOfQuestionsInGame;
        getRoomsResponseJson["Rooms"]["room" + std::to_string(i + 1)]["timePerQuestion"] = getRoomsResponse._rooms[i].timePerQuestion;
        getRoomsResponseJson["Rooms"]["room" + std::to_string(i + 1)]["isActive"] = getRoomsResponse._rooms[i].isActive;
        getRoomsResponseJson["Rooms"]["room" + std::to_string(i + 1)]["name"] = getRoomsResponse._rooms[i].name;
    }

    return createBufferFromJson(getRoomsResponseJson, GET_ROOM_CODE);
}

/*
*   Function will get a response struct and return a binary buffer representation
*   Input:
*       GetPlayersInRoomResponse getPlayersInRoomResponse - sturct to get it's attributes into buffer
*   Output:
*       std::vector<unsigned char> - a buffer (binary) to send to client
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse getPlayersInRoomResponse)
{
    nlohmann::json getPlayersInRoomResponseJson = getPlayersInRoomResponse;
    return createBufferFromJson(getPlayersInRoomResponseJson, GET_PLAYERS_IN_ROOM_CODE);
}

/*
*   Function will get a response struct and return a binary buffer representation
*   Input:
*       JoinRoomResponse joinRoomResponse - sturct to get it's attributes into buffer
*   Output:
*       std::vector<unsigned char> - a buffer (binary) to send to client
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomResponse)
{
    nlohmann::json joinRoomResponseJson = joinRoomResponse;
    return createBufferFromJson(joinRoomResponseJson, JOIN_ROOM_CODE);
}

/*
*   Function will get a response struct and return a binary buffer representation
*   Input:
*       CreateRoomResponse createRoomResponse - sturct to get it's attributes into buffer
*   Output:
*       std::vector<unsigned char> - a buffer (binary) to send to client
*/
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomResponse)
{
    nlohmann::json createRoomResponseJson = createRoomResponse;
    return createBufferFromJson(createRoomResponseJson, CREATE_ROOM_CODE);
}

/*
*   Function will get a string and return binary representation of the string
*   Input:
*       string - string to convert to binary
*   Output:
*       string - the binary result of the given string
*   
*/
std::string JsonResponsePacketSerializer::turnStringIntoBinary(std::string stringToBin)
{
    int i = 0;
    std::string stringBinary = "";
    for (i = 0; i < stringToBin.length(); i++)
    {
        stringBinary += std::bitset<BYTE_SIZE>(stringToBin[i]).to_string();
    }
    return stringBinary;
}

/*
*   Function will remove '_' and the first two '"' from the given message (unneeded chars)
*   Input:
*       string - string to clean (remove unneeded chars)
*   Output:
*       string - the string after removing unneeded chars
*/
std::string JsonResponsePacketSerializer::removeUnneededCharacters(std::string stringToClean)
{
    int i = 0;
    stringToClean = stringToClean.ERASE_UNDERSCORE;
    while (i != 1)
    {
        stringToClean.erase(stringToClean.find('"'), 1);
        i++;
    }
    return stringToClean;
}

/*
*   Function will create the buffer (result buffer) from json
*   Input:
*       nlohmann::json ResponseJson - json to convert to binary buffer
        int codeResponse - response code
    Output:
        std::vector<unsigned char> - a buffer (binary) to send to client
        
*/
std::vector<unsigned char> JsonResponsePacketSerializer::createBufferFromJson(nlohmann::json ResponseJson, int codeResponse)
{
    std::vector<unsigned char> buffer;
    std::string code = std::bitset<BYTE_SIZE>(codeResponse).to_string();
    std::string messageToClient = "";
    std::string messageSize = "";

    messageToClient = removeUnneededCharacters(ResponseJson.dump());
    messageSize = std::bitset<BYTE_SIZE* AMOUNT_OF_BYTES>(messageToClient.length()).to_string();
    messageToClient = turnStringIntoBinary(messageToClient);
    buffer.insert(buffer.end(), code.begin(), code.end());
    buffer.insert(buffer.end(), messageSize.begin(), messageSize.end());
    buffer.insert(buffer.end(), messageToClient.begin(), messageToClient.end());
    return buffer;
}


