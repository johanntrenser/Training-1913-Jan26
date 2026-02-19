#include <string>
#include <vector>
#pragma once
#include "User.h"
class Group
{
private:
	static int m_nextGroupId;
	int m_groupId;
	std::string m_groupName;
	std::vector<User*> m_students;
public:
	Group() : m_groupId(0), m_groupName(""), m_students() {}
	Group(std::string groupName) : m_groupId(m_nextGroupId++), m_groupName(groupName), m_students() {}
	int getGroupId();
	void setGroupId(int groupId);
	std::string getGroupName();
	void setGroupName(std::string groupName);
	std::vector<User*>& getStudentsInGroup();
	void addStudentToGroup(User* student);
	~Group() = default;
};

