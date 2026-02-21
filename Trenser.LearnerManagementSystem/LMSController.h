#include <iostream>
#include <vector>
#include <memory>
#pragma once
#include "User.h"
#include "Group.h"
#include "Enrollment.h"
#include "Course.h"
#include "FileManager.h"
#include "Authentication.h"

class LMSController
{
private:
	User* m_user;
	std::vector<std::shared_ptr<Course>> m_courses;
	std::vector<std::shared_ptr<Group>> m_groups;
	std::vector<std::shared_ptr<Enrollment>> m_enrollments;
public:
	LMSController() = default;
	LMSController(User* user) : m_user(user) {}
	~LMSController() = default;
	std::string getUserRole();
	void addCourse();
	void addStudent();
	void addInstructor();
	void addAdministrator();
	void removeStudent();
	void removeInstructor();
	void removeAdministrator();
	void listStudents();
	void listAdminstrators();
	void listInstructors();
	void listAllUsers();
	void listStudentNames();
	void listCourses();
	void listGroups();
	void enrollStudentToCourse();
	void enrollStudentToGroup();
	void addGroup();
	void removeGroup();
	bool IsStudentEnrolledInCourse(int studentId, int courseId);
	void loadAllFiles();
	void saveAllFiles();
};

