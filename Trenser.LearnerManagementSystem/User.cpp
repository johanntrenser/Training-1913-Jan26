#include "User.h"

int User::m_nextUserId = 2;

int User::getId()
{
    return m_userId;
}

std::string User::getUserName()
{
    return m_userName;
}

void User::setUserName(std::string userName)
{
    m_userName = userName;
}

std::string User::getPassword()
{
    return m_password;
}

void User::setPassword(std::string password)
{
    m_password = password;
}

std::string User::getRole()                
{
    return m_role;
}

std::string User::getStatus()
{
    return m_status;
}

void User::setStatus(std::string status)
{
    m_status = status;
}
