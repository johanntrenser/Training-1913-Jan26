#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#pragma once
#include "User.h"
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "FileManager.h"

class Authentication
{
private:
	std::vector<User*> m_users;    //User pointer is required to store child objects
	Authentication() = default;
public:
	User* login();
	std::string registerUser();
	void addUser(User* user);
	void deleteUser(int userId);
	User* getUser(int userId);
	const std::vector<User*>& getUsers() const;
	bool loadUsersFromFile();
	bool saveUsersToFile();
	Authentication(const Authentication&) = delete;
	Authentication& operator=(const Authentication&) = delete;
	static Authentication& getInstance();
	~Authentication();
};

