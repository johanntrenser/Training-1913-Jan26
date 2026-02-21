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
	bool isMenuActive = true;
	int choice = 0;
	while (isMenuActive)
	{
		cout << "===================STUDENT MENU===================" << endl;
		cout << "\n1.Logout\nEnter choice: ";
		cin >> choice;
		while (choice != 1)
		{
			cout << "Invalid choice! Please select a valid option: " << endl;
			cin >> choice;
		}
		if (choice == 1)
		{
			isMenuActive = false;
		}
	}
}

void Menu::instructorMenu()
{
	bool isMenuActive = true;
	int choice = 0;
	while (isMenuActive)
	{
		cout << "===================INSTRUCTOR MENU===================" << endl;
		cout << "\n1.Logout\nEnter choice: ";
		cin >> choice;
		while (choice != 1)
		{
			cout << "Invalid choice! Please select a valid option: " << endl;
			cin >> choice;
		}
		if (choice == 1)
		{
			isMenuActive = false;
		}
	}
}

void Menu::adminMenu()
{
	bool isMenuActive = true;
	int choice = 0;
	while (isMenuActive)
	{
		cout << "===================ADMIN MENU===================" << endl;
		cout << "1. Add Administrators\n"
			<< "2. Add Student\n"
			<< "3. Add Instructor\n"
			<< "4. Remove Administrator\n"
			<< "5. Remove Student\n"
			<< "6. Remove Instructor\n"
			<< "7. Add Course\n"
			<< "8. Logout\n"
			<< "Enter your choice (1 - 8): ";
		cin >> choice;
		while (choice < 1 || choice > 8)
		{
			cout << "Invalid choice! Please select a valid option : " << endl;
			cin >> choice;
		}
		cout << endl;
		if (m_lmsController->getUserRole() == "student" || m_lmsController->getUserRole() == "instructor")
		{
			cout << "User is authorized to access administrator menu!" << endl;
		}
		if (choice == 1)
		{
			m_lmsController->addAdministrator();
		}
		else if (choice == 2)
		{
			m_lmsController->addStudent();
		}
		else if (choice == 3)
		{
			m_lmsController->addInstructor();
		}
		else if (choice == 4)
		{
			m_lmsController->removeAdministrator();
		}
		else if (choice == 5)
		{
			m_lmsController->removeStudent();
		}
		else if (choice == 6)
		{
			m_lmsController->removeInstructor();
		}
		else if (choice == 7)
		{
			m_lmsController->addCourse();
		}
		else if (choice == 8)
		{
			isMenuActive = false;
		}
	}
}
