#include "Menu.h"
using namespace std;

void Menu::startSession()
{
	if(m_lmsController->getUserRole() == "student")
	{
		studentMenu();
	}
	else if(m_lmsController->getUserRole() == "instructor")
	{
		instructorMenu();
	}
	else if (m_lmsController->getUserRole() == "admin")
	{
		adminMenu();
	}
}

void Menu::studentMenu()
{
	cout << "===================STUDENT MENU===================" << endl;
}

void Menu::instructorMenu()
{
	cout << "===================INSTRUCTOR MENU===================" << endl;
}

void Menu::adminMenu()
{
	cout << "===================ADMIN MENU===================" << endl;
}
