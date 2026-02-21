#include <iostream>
#pragma once
#include "User.h"

class Instructor : public User
{
public:
	Instructor() = default;
	Instructor(std::string userName, std::string name, std::string password) : User(User::m_nextUserId++, userName, name, password, "instructor", "active") {}
	Instructor(int id, std::string userName, std::string name, std::string password, std::string role, std::string status) : User(id, userName, name, password, role, status) {}
	~Instructor() = default;
};

