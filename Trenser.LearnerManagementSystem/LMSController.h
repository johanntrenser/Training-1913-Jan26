#include <iostream>
#include <vector>
#include <memory>
#pragma once
#include "User.h"
#include "Group.h"
#include "Enrollment.h"
#include "Course.h"
class LMSController
{
private:
	User* m_user;
	std::vector<Course> m_courses;
	std::vector<Group> m_groups;
	std::vector<Enrollment> m_enrollments;
public:
	LMSController() = default;
	LMSController(User* user) : m_user(user) {}
	~LMSController() = default;
	std::string getUserRole();
};

