#include "Enrollment.h"

int Enrollment::m_nextEnrollmentId = 1;

int Enrollment::getEnrolledStudentId()
{
	return m_student->getId();
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

void Enrollment::setGroup(std::shared_ptr<Group> group)
{
	m_group = group;
}
