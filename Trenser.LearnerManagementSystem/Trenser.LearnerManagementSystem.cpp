//********************AUTHOR: JOHANN DOMINIC THOMAS**************
//********************DATE: 19-02-2026****************
#include <iostream>
#include <memory>
using namespace std;
#include "Authentication.h"
#include "LMSController.h"
#include "Menu.h"
#include "FileManager.h"

int main()
{
	const std::string USER_FILE_PATH = "C:\\Users\\1913\\Desktop\\Training-1913-Jan26\\files\\users.txt";
	const std::string COURSE_FILE_PATH = "";
	const std::string GROUPS_FILE_PATH = "";
	const std::string ENROLLMENT_FILE_PATH = "";
	const std::string ID_FILE_PATH = "";
	FileManager::setFilePaths(USER_FILE_PATH, COURSE_FILE_PATH, GROUPS_FILE_PATH, ENROLLMENT_FILE_PATH, ID_FILE_PATH);
	Authentication& authentication = Authentication::getInstance();
	shared_ptr<LMSController> lmsController = nullptr;
	bool isMenuActive = true;
	int choice = 0;
	std::string statusMessage = "";
	try
	{
		if (!authentication.loadUsersFromFile())
		{
			cout << "Failed to load users from file!" << endl;
			return 0;
		}
		else
		{
			cout << "Loaded users from file successfully!" << endl;
		}
		while (isMenuActive)
		{
			cout << "========================USER MENU=======================\n";
			cout << "1.Login\n2.Register\n3.Exit\nEnter your choice: ";
			cin >> choice;
			cout << endl;
			if (choice == 1)
			{
				User* user = authentication.login();
				if (user != nullptr)
				{
					cout << "Login Successfull\n" << endl;
					lmsController = make_shared<LMSController>(user);
					Menu menu = Menu(lmsController);
					menu.startSession();
				}
				else
				{
					cout << "User doesn't exist! Please try again\n" << endl;
				}
			}
			else if (choice == 2)
			{
				statusMessage = authentication.registerUser();
				cout << statusMessage << endl;
			}
			else if (choice == 3)
			{
				isMenuActive = false;
			}
			else
			{
				cout << "Invalid Option! Please Try again\n" << endl;
			}
		}
		if (!authentication.saveUsersToFile())
		{
			cout << "Failed to write users to file!" << endl;
		}
		else
		{
			cout << "Users wrote to file successfully!" << endl;
		}
	}
	catch (const exception& e)
	{
		cout << endl << e.what();
	}
}

