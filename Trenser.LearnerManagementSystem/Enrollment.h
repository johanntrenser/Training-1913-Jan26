#include <string>
#pragma once
class Enrollment
{
private:
	int m_studentId;
	int m_courseId;
	int m_numberOfCompletedModules;
	int m_progress;
	std::string m_grade;
	int m_groupId;
public:
	Enrollment() : m_studentId(0), m_courseId(0), m_numberOfCompletedModules(0), m_progress(0), m_grade(""), m_groupId(0) {}
	Enrollment(int studentId, int courseId, int numberOfCompletedModules, int progress, std::string grade, int groupId) : 
		m_studentId(studentId), m_courseId(courseId), m_numberOfCompletedModules(numberOfCompletedModules), m_progress(progress), m_grade(grade), m_groupId(groupId) {}
	~Enrollment() = default;
};

