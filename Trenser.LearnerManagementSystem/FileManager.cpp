#include "FileManager.h"

std::string FileManager::m_userFilePath = "";
std::string FileManager::m_courseFilePath = "";
std::string FileManager::m_groupsFilePath = "";
std::string FileManager::m_enrollmentFilePath = "";
std::string FileManager::m_idFilePath = "";

void FileManager::setFilePaths(const std::string userFilePath,const std::string courseFilePath, const std::string groupsFilePath, const std::string enrollmentFilePath, const std::string idFilePath)
{
	m_userFilePath = userFilePath;
	m_courseFilePath = courseFilePath;
	m_groupsFilePath = groupsFilePath;
	m_enrollmentFilePath = enrollmentFilePath;
	m_idFilePath = idFilePath;
}

bool FileManager::loadIdsFromFile()
{
	std::ifstream idFileReader(m_idFilePath, std::ios::in);
	if (!idFileReader.is_open())
	{
		return false;
	}
	bool skipHeader = true;
	std::string currentLine;
	while (getline(idFileReader, currentLine))
	{
		if (skipHeader)
		{
			skipHeader = false;
			continue;
		}
		if (currentLine.empty()) //empty lines after content
		{
			continue;
		}
		std::stringstream currentIds(currentLine);
		std::string userId, groupId, courseId, enrollmentId;
		getline(currentIds, userId, ',');
		getline(currentIds, groupId, ',');
		getline(currentIds, courseId, ',');
		getline(currentIds, enrollmentId, ',');
		User::m_nextUserId = std::stoi(userId);
		Group::m_nextGroupId = std::stoi(groupId);
		Course::m_nextCourseId = std::stoi(courseId);
		Enrollment::m_nextEnrollmentId = std::stoi(enrollmentId);
	}
	idFileReader.close();
	return true;
}

bool FileManager::saveIdsToFile()
{
	std::ofstream idFileWriter(m_idFilePath, std::ios::out | std::ios::trunc);
	if (!idFileWriter.is_open())
	{
		return false;
	}
	idFileWriter << "userId,groupId,courseId,enrollmentId" << std::endl;
	idFileWriter << User::m_nextUserId << "," << Group::m_nextGroupId << "," << Course::m_nextCourseId << "," << Enrollment::m_nextEnrollmentId;
	idFileWriter << std::endl;
	idFileWriter.close();
	return true;
}

bool FileManager::loadCoursesFromFile(std::vector<std::shared_ptr<Course>>& courses)
{
	std::ifstream fileReader(FileManager::m_courseFilePath, std::ios::in);
	if (!fileReader.is_open())
	{
		return false;
	}
	fileReader.clear();
	fileReader.seekg(0, std::ios::beg);
	bool skipHeader = true;
	std::string currentLine;
	while (getline(fileReader, currentLine))
	{
		if (skipHeader)
		{
			skipHeader = false;
			continue;
		}
		std::stringstream currentCourse(currentLine);
		std::string id, title, deadline, totalNumberOfModules;
		getline(currentCourse, id, ',');
		getline(currentCourse, title, ',');
		getline(currentCourse, deadline, ',');
		getline(currentCourse, totalNumberOfModules, ',');
		courses.push_back(std::make_shared<Course>(std::stoi(id.substr(1)), title, deadline, stoi(totalNumberOfModules)));
	}
	fileReader.close();
	return true;
}

bool FileManager::saveCoursesToFile(const std::vector<std::shared_ptr<Course>>& courses)
{
	std::ofstream fileWriter(m_courseFilePath, std::ios::out | std::ios::trunc);
	if (!fileWriter.is_open())
	{
		return false;
	}
	fileWriter << "courseId,title,deadline,totalNumberOfModules" << std::endl;
	for (std::vector<std::shared_ptr<Course>>::const_iterator iterator = courses.begin(); iterator != courses.end(); ++iterator)
	{
		fileWriter << "C";
		fileWriter << (*iterator)->getCourseId() << "," << (*iterator)->getCourseTitle() << "," << (*iterator)->getCourseDeadline() << "," << (*iterator)->getTotalNumberOfModules();
		fileWriter << std::endl;
	}
	fileWriter.close();
	return true;
}
