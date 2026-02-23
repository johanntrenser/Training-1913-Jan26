#include "Course.h"

int Course::m_nextCourseId = 1;

int Course::getCourseId()
{
	return m_courseId;
}

void Course::setCourseId(int courseId)
{
	m_courseId = courseId;
}

std::string Course::getCourseTitle()
{
	return m_title;
}

void Course::setCourseTitle(std::string courseTitle)
{
	m_title = courseTitle;
}

std::string Course::getCourseDeadline()
{
	return m_deadline;
}

void Course::setCourseDeadline(std::string courseDeadline)
{
	m_deadline = courseDeadline;
}

int Course::getTotalNumberOfModules()
{
	return m_totalNumberOfModules;
}

void Course::setTotalNumberOfModules(int totalNumberOfModules)
{
	m_totalNumberOfModules = totalNumberOfModules;
}

std::string Course::getStatus()
{
	return m_status;
}

void Course::setStatus(std::string status)
{
	m_status = status;
}



