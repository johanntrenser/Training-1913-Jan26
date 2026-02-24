#include <iostream>
#pragma once
#include "User.h"

class Student : public User
{
public:
	Student() = default;
	Student(std::string userName, std::string name, std::string password) : User(User::m_nextUserId++, userName, name, password, STUDENT_ROLE, "active") {}
	Student(int id, std::string userName, std::string name, std::string password, std::string role, std::string status) : User(id, userName, name, password, role, status) {}
	static const std::string STUDENT_ROLE;
	~Student() = default;
};

