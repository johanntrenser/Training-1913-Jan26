#include <iostream>
#pragma once
#include "User.h"

class Student : public User
{
public:
	Student() = default;
	Student(std::string userName, std::string password) : User(User::m_nextUserId++, userName, password, "student") {}
	Student(int id, std::string userName, std::string password, std::string role) : User(id, userName, password, role) {}
	~Student() = default;
};

