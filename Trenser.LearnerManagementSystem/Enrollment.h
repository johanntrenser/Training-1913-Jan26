#include <string>
#pragma once
#include "User.h"
#include "Group.h"
#include "Course.h"
class Enrollment
{
private:
	User* m_student;
	Course* m_course;
	int m_numberOfCompletedModules;
	int m_progress;
	std::string m_grade;
	Group* m_group;
public:
	Enrollment() : m_student(nullptr), m_course(nullptr), m_numberOfCompletedModules(0), m_progress(0), m_grade(""), m_group(nullptr) {}
	Enrollment(User* student, Course* course, int numberOfCompletedModules, int progress, std::string grade, Group* group) : 
		m_student(student), m_course(course), m_numberOfCompletedModules(numberOfCompletedModules), m_progress(progress), m_grade(grade), m_group(group) {}
	~Enrollment() = default;
};

