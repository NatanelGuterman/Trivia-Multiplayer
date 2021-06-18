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
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::vector<std::string> getAllUsers();
	void set_m_metdata(RoomData data);
	void set_m_users(std::vector<LoggedUser> users);

private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;

};
