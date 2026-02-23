#include "Enrollment.h"

int Enrollment::m_nextEnrollmentId = 1;

int Enrollment::getEnrolledStudentId()
{
	return m_student->getId();
}

std::string Enrollment::getEnrolledStudentName()
{
	return m_student->getName();
}

int Enrollment::getEnrolledCourseId()
{
	std::shared_ptr<Course> coursePtr = m_course.lock();
	if (coursePtr != nullptr)
	{
		return coursePtr->getCourseId();
	}
	else
	{
		return -1;
	}
}

int Enrollment::getEnrolledGroupId()
{
	std::shared_ptr<Group> groupPtr = m_group.lock();
	if (groupPtr != nullptr)
	{
		groupPtr->getGroupId();
	}
	else
	{
		return -1;
	}
}

int Enrollment::getEnrollmentId()
{
	return m_enrollmentId;
}

int Enrollment::getProgress()
{
	return m_progress;
}

std::string Enrollment::getGrade()
{
	return m_grade;
}

void Enrollment::setGrade(std::string grade)
{
	m_grade = grade;
}

int Enrollment::getNumberOfCompletedModules()
{
	return m_numberOfCompletedModules;
}

void Enrollment::setGroup(std::shared_ptr<Group> group)
{
	m_group = group;
}

void Enrollment::setNumberOfCompletedModules(int modules)
{
	m_numberOfCompletedModules = modules;
}

void Enrollment::setProgress(int progress)
{
	m_progress = progress;
}
