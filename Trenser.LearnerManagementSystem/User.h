//**********AUTHOR: JOHANN DOMINIC THOMAS************
//**********DATE: 17-02-2026*************

#pragma once
#include <string>

class User
{
protected:
	int m_userId;
	std::string m_userName;
	std::string m_name;
	std::string m_password;
	std::string m_role;
	std::string m_status;
public:
	static int m_nextUserId;
	User() : m_userId(0), m_userName(""), m_name(""), m_password(""), m_role(""), m_status("") {}
	User(int userId, std::string userName, std::string name, std::string password, std::string role, std::string status) :
		m_userId(userId), m_userName(userName), m_name(name), m_password(password), m_role(role), m_status(status) {
	}
	int getId();
	std::string getUserName();
	void setUserName(std::string userName);
	std::string getName();
	void setName(std::string name);
	std::string getPassword();
	void setPassword(std::string password);
	std::string getRole();
	bool getStatus();
	void setStatus(bool status);
	virtual ~User() {}
};

