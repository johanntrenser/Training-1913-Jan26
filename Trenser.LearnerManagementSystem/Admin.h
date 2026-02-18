#include <iostream>
#pragma once
#include "User.h"

class Admin : public User
{
public:
	Admin() {}
	Admin(std::string userName, std::string password) : User(User::m_nextUserId++, userName, password, "admin") {}
	~Admin() {}
};

