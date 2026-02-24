#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
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
	void listStudentsInGroup();
	void listStudentsProgressInCourse();
	void listStudentsGradeInCourse();
	void listStudentGrades();
	void listEnrolledCourses();
	void listEnrolledGroups();
	void listStudentProgress();
	std::shared_ptr<Course> getCourse(int courseId);
	User* getUser(int userId);
	std::shared_ptr<Group> getGroup(int groupId);
	void addGroup();
	void removeCourse();
	void updateCourseDetails(std::shared_ptr<Course> course);
	void removeGroup();
	void enrollStudentToCourse();
	void enrollStudentToGroup();
	void enrollToCourse();
	void completeModule();
	void gradeStudent();
	int getNumberOfStudents();
	int getNumberOfInstructors();
	int getNumberOfStudentsEnrolledInCourse(int courseId);
	int getStudentEnrollmentsCount(int studentId);
	int getStudentPendingEnrollmentsCount(int studentId);
	bool IsStudentEnrolledInCourse(int studentId, int courseId);
	bool IsStudentEnrolledInGroup(int studentId, int groupId);
	bool IsStudentEnrolledInGroupsCourse(int studentId, int groupId);
	void viewStudentsInMyGroup();
	std::string getValidatedGrade();
	int getValidatedUserId();
	int getValidatedGroupId();
	int getValidatedCourseId();
	void loadAllFiles();
	void saveAllFiles();
};

