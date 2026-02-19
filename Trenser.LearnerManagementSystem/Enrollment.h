#include <string>
#include <memory>
#pragma once
#include "User.h"
#include "Group.h"
#include "Course.h"
class Enrollment
{
private:
	User* m_student;
	std::weak_ptr<Course> m_course;
	int m_numberOfCompletedModules;
	int m_progress;
	std::string m_grade;
	std::weak_ptr<Group> m_group;
public:
	Enrollment() : m_student(nullptr), m_numberOfCompletedModules(0), m_progress(0), m_grade("") {}
    Enrollment(User* student, std::shared_ptr<Course> course, int numberOfCompletedModules, int progress, std::string grade, std::shared_ptr<Group> group)
        : m_student(student),
        m_course(course),
        m_numberOfCompletedModules(numberOfCompletedModules),
        m_progress(progress),
        m_grade(grade),
        m_group(group) {}
	~Enrollment() = default;
};

