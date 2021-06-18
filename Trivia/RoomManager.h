#pragma once
#include "Room.h"
#include <map>


class RoomManager
{
public:
	void createRoom(LoggedUser loggedUser, RoomData roomData);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	std::vector<RoomData> getRooms();

private:
	std::map<int, Room> m_rooms;

};
