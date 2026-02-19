#include <string>
#include <vector>
#include <memory>
#pragma once
#include "User.h"
#include "Course.h"
class Group
{
private:
	int m_groupId;
	std::string m_groupName;
	std::weak_ptr<Course> m_course;
	std::vector<User*> m_students;
public:
	Group() : m_groupId(0), m_groupName(""), m_students() {}
	Group(std::string groupName, std::shared_ptr<Course> course) : m_groupId(m_nextGroupId++), m_groupName(groupName), m_course(course), m_students() {}
	static int m_nextGroupId;
	int getGroupId();
	void setGroupId(int groupId);
	std::string getGroupName();
	void setGroupName(std::string groupName);
	std::vector<User*>& getStudentsInGroup();
	void addStudentToGroup(User* student);
	~Group() = default;
};

