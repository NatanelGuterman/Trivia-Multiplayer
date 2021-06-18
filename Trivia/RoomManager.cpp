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

	this->m_rooms[roomData.id] = room;
}

/*
This function deletes a room fro the map, if the room is in the map.
input: int ID --> Room's id.
output: None.
*/

void RoomManager::deleteRoom(int ID)
{
	std::map<int, Room>::iterator iter = this->m_rooms.find(ID);
	if (iter != this->m_rooms.end())
	{
		this->m_rooms.erase(iter);
	}
}