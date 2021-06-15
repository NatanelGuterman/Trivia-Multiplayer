#include "Room.h"

/*
This function adds a new user to the vector of logged users in this room.
input: LoggedUser user --> The new user.
output: None.
*/
void Room::addUser(LoggedUser user)
{
	this->m_users.push_back(user);
}

/*
This function removes a user from the vector of logged users in this room.
input: LoggedUser user --> The user to remove.
output: None.
*/

void Room::removeUser(LoggedUser user)
{
	std::vector<LoggedUser>::iterator iter = this->m_users.begin();

	while (iter != this->m_users.end())
	{
		if ((*iter).getUsername() == user.getUsername())
		{
			this->m_users.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

/*
This function builds a vector with the names of all players in this room.
input: None.
output: std::vector<std::string> result --> Vector of the names.
*/

std::vector<std::string> Room::getAllUsers()
{
	std::vector<std::string> result;
	std::vector<LoggedUser>::iterator iter = this->m_users.begin();

	while (iter != this->m_users.end())
	{
		result.push_back((*iter).getUsername());
		iter++;
	}

	return result;
}
