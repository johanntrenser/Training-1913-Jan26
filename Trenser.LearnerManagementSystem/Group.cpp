#include "Group.h"

int Group::m_nextGroupId = 1;

int Group::getGroupId()
{
    return m_groupId;
}

void Group::setGroupId(int groupId)
{
    m_groupId = groupId;
}

std::string Group::getGroupName()
{
    return m_groupName;
}

void Group::setGroupName(std::string groupName)
{
    m_groupName = groupName;
}

std::vector<int>& Group::getStudentsInGroup()
{
    return m_students;
}

void Group::addStudentToGroup(int studentId)
{
    m_students.push_back(studentId);
}
