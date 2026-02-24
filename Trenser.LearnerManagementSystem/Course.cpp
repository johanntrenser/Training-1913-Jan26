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

bool Course::getStatus()
{
    if (m_status == "active")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Course::setStatus(bool status)
{
    if (status)
    {
        m_status = "active";
    }
    else
    {
        m_status = "inactive";
    }
}


