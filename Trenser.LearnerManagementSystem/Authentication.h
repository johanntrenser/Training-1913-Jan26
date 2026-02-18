#include <iostream>
#include <vector>
#pragma once
#include "User.h"
#include "Student.h"
#include "Instructor.h"

class Authentication
{
private:
	std::vector<User*> m_users;    //User pointer is required to store child objects
public:
	Authentication() = default;
	User* login();
	std::string registerUser();
	~Authentication() = default;
};

