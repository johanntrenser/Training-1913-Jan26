#include <string>
#pragma once

class Course
{
private:
	int m_courseId;
	std::string m_title;
	std::string m_deadline;
	int m_totalNumberOfModules;
	std::string m_status;
public:
	Course() : m_courseId(0), m_title(""), m_deadline(""), m_totalNumberOfModules(0), m_status("") {}
	Course(std::string title, std::string deadline, int totalNumberOfModules) :
		m_courseId(m_nextCourseId++),
		m_title(title), m_deadline(deadline),
		m_totalNumberOfModules(totalNumberOfModules),
		m_status("active") {}
	Course(int courseId, std::string title, std::string deadline, int totalNumberOfModules, std::string status) :
		m_courseId(courseId),
		m_title(title), m_deadline(deadline),
		m_totalNumberOfModules(totalNumberOfModules),
		m_status(status) {}
	static int m_nextCourseId;
	int getCourseId();
	void setCourseId(int courseId);
	std::string getCourseTitle();
	void setCourseTitle(std::string courseTitle);
	std::string getCourseDeadline();
	void setCourseDeadline(std::string courseDeadline);
	int getTotalNumberOfModules();
	void setTotalNumberOfModules(int totalNumberOfModules);
	bool getStatus();
	void setStatus(bool status);
	~Course() = default;
};

