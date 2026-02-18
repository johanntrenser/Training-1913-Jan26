#include "FileManager.h"

std::string FileManager::m_userFilePath = "";
std::string FileManager::m_courseFilePath = "";
std::string FileManager::m_groupsFilePath = "";
std::string FileManager::m_enrollmentFilePath = "";
std::string FileManager::m_idFilePath = "";

void FileManager::setFilePaths(std::string userFilePath, std::string courseFilePath, std::string groupsFilePath, std::string enrollmentFilePath, std::string idFilePath)
{
	m_userFilePath = userFilePath;
	m_courseFilePath = courseFilePath;
	m_groupsFilePath = groupsFilePath;
	m_enrollmentFilePath = enrollmentFilePath;
	m_idFilePath = idFilePath;
}
