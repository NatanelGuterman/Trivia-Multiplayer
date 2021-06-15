#pragma once
#include <vector>
#include "LoggedUser.h"

struct RoomData {
	unsigned int id, maxPlayers, numOfQuestionsInGame, timePerQuestion, isActive;
	std::string name;
} typedef RoomData;


class Room
{
public:
	void addUser(LoggedUser);
	void removeUser(LoggedUser);
	std::vector<std::string> getAllUsers();

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

};
