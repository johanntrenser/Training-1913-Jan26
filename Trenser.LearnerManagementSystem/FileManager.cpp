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
		std::stringstream currentIds(currentLine);
		std::string userId, groupId, courseId;
		getline(currentIds, userId, ',');
		getline(currentIds, groupId, ',');
		getline(currentIds, courseId, ',');
		User::m_nextUserId = std::stoi(userId);
		Group::m_nextGroupId = std::stoi(groupId);
		Course::m_nextCourseId = std::stoi(courseId);
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
	idFileWriter << "userId,groupId,courseId" << std::endl;
	idFileWriter << User::m_nextUserId << "," << Group::m_nextGroupId << "," << Course::m_nextCourseId;
	idFileWriter << std::endl;
	idFileWriter.close();
	return true;
}
