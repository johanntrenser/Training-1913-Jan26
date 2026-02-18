//**********AUTHOR: JOHANN DOMINIC THOMAS************
//**********DATE: 17-02-2026*************

#pragma once
#include <string>

class User
{
protected:
	static int m_nextUserId;
	int m_userId;
	std::string m_userName;
	std::string m_password;
	std::string m_role;
public:
	User() : m_userId(0), m_userName(""), m_password(""), m_role("") {}
	User(int userId, std::string userName, std::string password, std::string role) : m_userId(userId), m_userName(userName), m_password(password), m_role(role) {}
	int getId();
	std::string getUserName();
	void setUserName(std::string userName);
	std::string getPassword();
	void setPassword(std::string password);
	std::string getRole();
	virtual ~User() {}
};

