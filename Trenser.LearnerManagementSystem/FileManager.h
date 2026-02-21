#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#pragma once
#include "User.h"
#include "Course.h"
#include "Group.h"
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
	static void setFilePaths(std::string userFilePath, std::string courseFilePath, std::string groupsFilePath, std::string enrollmentFilePath, std::string idFilePath);
	static bool loadIdsFromFile();
	static bool saveIdsToFile();
	static bool loadCoursesFromFile(std::vector<std::shared_ptr<Course>>& courses);
	static bool saveCoursesToFile(const std::vector<std::shared_ptr<Course>>& courses);
};

