#include <iostream>
#pragma once
#include "User.h"

class Admin : public User
{
public:
	Admin() {}
	Admin(std::string userName, std::string name, std::string password) : User(User::m_nextUserId++, userName, name, password, "admin", "active") {}
	Admin(int id, std::string userName, std::string name, std::string password, std::string role, std::string status) : User(id, userName, name, password, role, status) {}
	~Admin() {}
};

