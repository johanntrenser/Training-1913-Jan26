#include "LMSController.h"
using namespace std;

std::string LMSController::getUserRole()
{
    return m_user->getRole();
}

void LMSController::addCourse()
{
}

void LMSController::addStudent()
{
}

void LMSController::addInstructor()
{
}

void LMSController::addAdministrator()
{
}

void LMSController::removeStudent()
{
}

void LMSController::removeInstructor()
{
}

void LMSController::removeAdministrator()
{
}

void LMSController::loadAllFiles()
{
    cout << "\nLoading Files............\n" << endl;
    if (!FileManager::loadIdsFromFile())
    {
        cout << "Failed to load ids from file!" << endl;
    }
    else
    {
        cout << "Loaded ids from file successfully!" << endl;
    }
}

void LMSController::saveAllFiles()
{
    cout << "\nSaving datas to file........\n" << endl;
    if (!FileManager::saveIdsToFile())
    {
        cout << "Failed to write ids to file!" << endl;
    }
    else
    {
        cout << "Saved ids to file successfully!" << endl;
    }
}
