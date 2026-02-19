#include <iostream>
#pragma once
#include "User.h"

class Admin : public User
{
public:
	Admin() {}
	Admin(std::string userName, std::string password) : User(User::m_nextUserId++, userName, password, "admin") {}
	Admin(int id, std::string userName, std::string password, std::string role) : User(id, userName, password, role) {}
	~Admin() {}
};

