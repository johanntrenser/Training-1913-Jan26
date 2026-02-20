#include "LMSController.h"
using namespace std;

std::string LMSController::getUserRole()
{
    return m_user->getRole();
}

void LMSController::addCourse()
{
    string title, deadline;
    int numberOfModules = 0;
    bool isExisting = true;
    cin.ignore(10000, '\n');
    while (isExisting)
    {
        cout << "Enter the course title: ";
        getline(cin, title);
        if (title.empty())
        {
            cout << "Title cannot be empty. Please try again.\n";
            continue;
        } 
        isExisting = false;
        for (vector<shared_ptr<Course>>::iterator iterator = m_courses.begin(); iterator != m_courses.end(); ++iterator)
        {
            if ((*iterator)->getCourseTitle() == title)
            {
                cout << "Course already exists!\n";
                isExisting = true;
                break;
            }
        }
    }
    while (deadline.empty())
    { 
        cout << "Enter the deadline: ";
        getline(cin, deadline);
        if (deadline.empty())
        {
            cout << "Deadline cannot be empty. Please try again.\n";
        }
    } 
    while (true)
    {
        cout << "Enter the number of modules: ";
        if (cin >> numberOfModules && numberOfModules > 0)
        {
            break;
        }
        else
        {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear(); // clear error flag
            cin.ignore(10000, '\n'); // discard up to 10000 chars until newline
            
        }
    }
    m_courses.push_back(make_shared<Course>(title, deadline, numberOfModules));
    cout << "Course Added Successfully!" << endl;
}

void LMSController::addStudent()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    int choice;
    string username = "";
    string password = "";
    bool isExisting = true;
    while (isExisting)
    {
        cout << "Enter the username: ";
        cin >> username;
        isExisting = false;
        for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
        {
            if (((*iterator)->getUserName() == username))
            {
                cout << "Username already exists!" << endl;
                isExisting = true;
                break;
            }
        }
    }
    cout << "Enter your password: ";
    cin >> password;
    authentication.addUser(new Student(username, password));
    cout << "Student added successfully!\n" << endl;
}

void LMSController::addInstructor()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    int choice;
    string username = "";
    string password = "";
    bool isExisting = true;
    while (isExisting)
    {
        cout << "Enter the username: ";
        cin >> username;
        isExisting = false;
        for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
        {
            if (((*iterator)->getUserName() == username))
            {
                cout << "Username already exists!" << endl;
                isExisting = true;
                break;
            }
        }
    }
    cout << "Enter your password: ";
    cin >> password;
    authentication.addUser(new Instructor(username, password));
    cout << "Instructor added successfully!\n" << endl;
}

void LMSController::addAdministrator()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    int choice;
    string username = "";
    string password = "";
    bool isExisting = true;
    while (isExisting)
    {
        cout << "Enter the username: ";
        cin >> username;
        isExisting = false;
        for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
        {
            if (((*iterator)->getUserName() == username))
            {
                cout << "Username already exists!" << endl;
                isExisting = true;
                break;
            }
        }
    }
    cout << "Enter your password: ";
    cin >> password;
    authentication.addUser(new Admin(username, password));
    cout << "Admin added successfully!\n" << endl;
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
    /*cout << "\nLoading Files............\n" << endl;
    if (!FileManager::loadIdsFromFile())
    {
        cout << "Failed to load ids from file!" << endl;
    }
    else
    {
        cout << "Loaded ids from file successfully!" << endl;
    }*/
}

void LMSController::saveAllFiles()
{
    /*cout << "\nSaving datas to file........\n" << endl;
    if (!FileManager::saveIdsToFile())
    {
        cout << "Failed to write ids to file!" << endl;
    }
    else
    {
        cout << "Saved ids to file successfully!" << endl;
    }*/
}
