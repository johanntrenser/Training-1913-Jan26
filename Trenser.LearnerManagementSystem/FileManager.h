#include <string>
#pragma once
class FileManager
{
private:
	FileManager() = default;  //FileManager class cannot be instantiated as constructor is private
public:
	static std::string m_userFilePath;
	static std::string m_courseFilePath;
	static std::string m_groupsFilePath;
	static std::string m_enrollmentFilePath;
	static std::string m_idFilePath;
	static void setFilePaths(std::string userFilePath, std::string courseFilePath, std::string groupsFilePath, std::string enrollmentFilePath, std::string m_idFilePath);
};

