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
	std::ifstream fileReader(m_courseFilePath, std::ios::in);
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

bool FileManager::loadGroupsFromFile(std::vector<std::shared_ptr<Group>>& groups, LMSController& lmsController)
{
	std::ifstream fileReader(m_groupsFilePath, std::ios::in);
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
		std::stringstream currentGroup(currentLine);
		std::string groupIdString, name, courseIdString, studentIdsString;
		getline(currentGroup, groupIdString, ',');
		getline(currentGroup, name, ',');
		getline(currentGroup, courseIdString, ',');
		getline(currentGroup, studentIdsString, ',');
		std::shared_ptr<Course> course = lmsController.getCourse(stoi(courseIdString));
		if (course == nullptr)
		{
			std::cout << "Course not found for this group!\n"; 
			continue; //skip group
		}
		std::shared_ptr<Group> group = std::make_shared<Group>(name, course);
		group->setGroupId(std::stoi(groupIdString.substr(1)));
		//load students
		std::stringstream currentStudents(studentIdsString);
		std::string studentIdString;
		while (getline(currentStudents, studentIdString, ';'))
		{
			if (!studentIdString.empty())
			{
				User* student = lmsController.getUser(std::stoi(studentIdString));
				if (student != nullptr)
				{
					group->addStudentToGroup(student);
				}
				else
				{
					std::cout << "Student " << studentIdString << " not found for Group " << name << "!\n";
				}
			}
		}
		groups.push_back(group);
	}
	fileReader.close();
	return true;
}

bool FileManager::saveGroupsToFile(const std::vector<std::shared_ptr<Group>>& groups)
{
	std::ofstream fileWriter(m_groupsFilePath, std::ios::out | std::ios::trunc);
	if (!fileWriter.is_open())
	{
		return false;
	}
	fileWriter << "groupId,groupName,courseId,studentIds" << std::endl;
	for (std::vector<std::shared_ptr<Group>>::const_iterator iterator = groups.begin(); iterator != groups.end(); ++iterator)
	{
		fileWriter << "G";
		fileWriter << (*iterator)->getGroupId() << "," << (*iterator)->getGroupName() << "," << (*iterator)->getGroupCourseId() << ",";
		const std::vector<User*>& students = (*iterator)->getStudentsInGroup();
		for (std::vector<User*>::const_iterator userIterator = students.begin(); userIterator != students.end(); ++userIterator)
		{
			User* student = *userIterator;
			if (student != nullptr)
			{
				fileWriter << student->getId();
				if (std::next(userIterator) != students.end())
				{
					fileWriter << ";";
				}
			}
		}
		fileWriter << std::endl;
	}
	fileWriter.close();
	return true;
}
