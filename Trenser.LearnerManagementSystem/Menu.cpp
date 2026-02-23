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
		cout << "1.  Enroll to Course\n"
			<< "2.  View Enrolled Courses\n"
			<< "3.  View Enrolled Groups\n"
			<< "4.  View Grades\n"
			<< "5.  Complete Course Modules\n"
			<< "6.  View Course Progress\n"
			<< "7.  View Students in Group\n"
			<< "8.  Logout\n"
			<< "Enter your choice (1 - 8): ";
		cin >> choice;
		while (choice < 1 || choice > 8)
		{
			cout << "Invalid choice! Please select a valid option: " << endl;
			cin >> choice;
		}
		if (choice == 1)
		{
			m_lmsController->enrollToCourse();
		}
		else if (choice == 2)
		{
			m_lmsController->listEnrolledCourses();
		}
		else if (choice == 3)
		{
			m_lmsController->listEnrolledGroups();
		}
		else if (choice == 4)
		{
			m_lmsController->listStudentGrades();
		}
		else if (choice == 5)
		{
			m_lmsController->completeModule();
		}
		else if (choice == 6)
		{
			m_lmsController->listStudentProgress();
		}
		else if (choice == 7)
		{
			m_lmsController->viewStudentsInMyGroup();
		}
		else if (choice == 8)
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
		cout << "1.  Enroll Student to Course\n"
			<< "2.  Enroll Student to Group\n"
			<< "3.  Grade Students\n"
			<< "4.  View Student Grades\n"
			<< "5.  View Student Progress\n"
			<< "6.  Add Group\n"
			<< "7.  Remove Group\n"
			<< "8.  View Groups\n"
			<< "9.  List All Students\n"
			<< "10. View Students in Group\n"
			<< "11. Logout\n"
			<< "Enter your choice (1 - 11): ";
		cin >> choice;
		while (choice < 1 || choice > 11)
		{
			cout << "Invalid choice! Please select a valid option : " << endl;
			cin >> choice;
		}
		cout << endl;
		if (m_lmsController->getUserRole() == "student")
		{
			cout << "User is not authorized to access instructor menu!" << endl;
		}
		if (choice == 1)
		{
			m_lmsController->enrollStudentToCourse();
		}
		else if (choice == 2)
		{
			m_lmsController->enrollStudentToGroup();
		}
		else if (choice == 3)
		{
			m_lmsController->gradeStudent();
		}
		else if (choice == 4)
		{
			m_lmsController->listStudentsGradeInCourse();
		}
		else if (choice == 5)
		{
			m_lmsController->listStudentsProgressInCourse();
		}
		else if (choice == 6)
		{
			m_lmsController->addGroup();
		}
		else if (choice == 7)
		{
			m_lmsController->removeGroup();
		}
		else if (choice == 8)
		{
			m_lmsController->listGroups();
		}
		else if (choice == 9)
		{
			m_lmsController->listStudents();
		}
		else if (choice == 10)
		{
			m_lmsController->listStudentsInGroup();
		}
		else if (choice == 11)
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
		cout << "1.  Add Administrator\n"
			 << "2.  Add Student\n"
			 << "3.  Add Instructor\n"
			 << "4.  Remove Administrator\n"
			 << "5.  Remove Student\n"
			 << "6.  Remove Instructor\n"
			 << "7.  Add Course\n"
			 << "8.  Remove Course\n"
			 << "9.  List Courses\n"
			 << "10. List Students\n"
			 << "11. List Instructors\n"
			 << "12. List Administrators\n"
			 << "13. List All Users\n"
			 << "14. Logout\n"
			 << "Enter your choice (1 - 14): ";
		cin >> choice;
		while (choice < 1 || choice > 14)
		{
			cout << "Invalid choice! Please select a valid option : " << endl;
			cin >> choice;
		}
		cout << endl;
		if (m_lmsController->getUserRole() == "student" || m_lmsController->getUserRole() == "instructor")
		{
			cout << "User is not authorized to access administrator menu!" << endl;
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
			m_lmsController->removeCourse();
		}
		else if (choice == 9)
		{
			m_lmsController->listCourses();
		}
		else if (choice == 10)
		{
			m_lmsController->listStudents();
		}
		else if (choice == 11)
		{
			m_lmsController->listInstructors();
		}
		else if (choice == 12)
		{
			m_lmsController->listAdminstrators();
		}
		else if (choice == 13)
		{
			m_lmsController->listAllUsers();
		}
		else if (choice == 14)
		{
			isMenuActive = false;
		}
	}
}
