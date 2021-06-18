#include "RoomManager.h"

/*
This function creates a room and adds it to the map.
input: LoggedUser loggedUser --> The creator.
	   RoomData roomData --> The data of the created room.
output: None.
*/

void RoomManager::createRoom(LoggedUser loggedUser, RoomData roomData)
{
	Room room;
	std::vector<LoggedUser> users;

	users.push_back(loggedUser);
	room.set_m_metdata(roomData);
	room.set_m_users(users);

	this->m_rooms[this->m_rooms.size() + 1] = room;
}
