#include <iostream>
#pragma once
#include "User.h"

class Instructor : public User
{
public:
	Instructor() = default;
	Instructor(std::string userName, std::string password) : User(User::m_nextUserId++, userName, password, "instructor", "active") {}
	Instructor(int id, std::string userName, std::string password, std::string role, std::string status) : User(id, userName, password, role, status) {}
	~Instructor() = default;
};

