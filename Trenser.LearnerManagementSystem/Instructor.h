#include <iostream>
#pragma once
#include "User.h"

class Instructor : public User
{
public:
	Instructor() = default;
	Instructor(std::string userName, std::string password) : User(User::m_nextUserId++, userName, password, "instructor") {}
	Instructor(int id, std::string userName, std::string password, std::string role) : User(id, userName, password, role) {}
	~Instructor() = default;
};

