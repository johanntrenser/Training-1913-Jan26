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
    int choice = 0;
    string username = "";
    string password = "";
    string name = "";
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
    cin.ignore(10000, '\n');
    cout << "Enter student name: ";
    getline(cin, name);
    while (name.empty())
    {
        cout << "Name cannot be empty! Please Enter name again: ";
        getline(cin, name);
    }
    authentication.addUser(new Student(username, name, password));
    cout << "Student added successfully!\n" << endl;
}

void LMSController::addInstructor()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    int choice = 0;
    string username = "";
    string password = "";
    string name = "";
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
    cout << "Enter  password: ";
    cin >> password;
    cin.ignore(10000, '\n');
    cout << "Enter instructor name: ";
    getline(cin, name);
    while (name.empty())
    {
        cout << "Name cannot be empty! Please Enter name again: ";
        getline(cin, name);
    }
    authentication.addUser(new Instructor(username, name, password));
    cout << "Instructor added successfully!\n" << endl;
}

void LMSController::addAdministrator()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    int choice = 0;
    string username = "";
    string password = "";
    string name = "";
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
    cout << "Enter password: ";
    cin >> password;
    cin.ignore(10000, '\n');
    cout << "Enter administrator name: ";
    getline(cin, name);
    while (name.empty())
    {
        cout << "Name cannot be empty! Please Enter name again: ";
        getline(cin, name);
    }
    authentication.addUser(new Admin(username, name, password));
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
    Authentication& authentication = Authentication::getInstance();
    int choice = 0;
    std::string userId;
    int id;
    listAdminstrators();
    cout << "Enter user id of administrator to delete: ";
    cin >> userId;
    while (userId.length() < 2 || userId[0] != 'U'  || isdigit(stoi(userId.substr(1))))
    {
        cout << "Invalid user id! Please Enter a valid user id: ";
        cin >> userId;
    }
    id = stoi(userId.substr(1)); //from 1st index
    authentication.deleteUser(id);
}

void LMSController::listStudents()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    cout << "============STUDENTS LIST==========" << endl;
    for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
    {
        if ((*iterator)->getRole() == "student" && (*iterator)->getStatus() != "inactive")
        {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Username: " << (*iterator)->getUserName() << endl;
            cout << "Name: " << (*iterator)->getName() << endl;
            cout << "Role: " << (*iterator)->getRole() << endl;
            cout << "Status: " << (*iterator)->getStatus() << "\n" << endl;
        }
    }
}

void LMSController::listAdminstrators()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    cout << "============ADMISTRATORS LIST==========" << endl;
    for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
    {
        if ((*iterator)->getRole() == "admin" && (*iterator)->getStatus() != "inactive")
        {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Username: " << (*iterator)->getUserName() << endl;
            cout << "Name: " << (*iterator)->getName() << endl;
            cout << "Role: " << (*iterator)->getRole() << endl;
            cout << "Status: " << (*iterator)->getStatus() << "\n" << endl;
        }
    }
}

void LMSController::listInstructors()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    cout << "============INSTRUCTORS LIST==========" << endl;
    for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
    {
        if ((*iterator)->getRole() == "instructor" && (*iterator)->getStatus() != "inactive")
        {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Username: " << (*iterator)->getUserName() << endl;
            cout << "Name: " << (*iterator)->getName() << endl;
            cout << "Role: " << (*iterator)->getRole() << endl;
            cout << "Status: " << (*iterator)->getStatus() << "\n" << endl;
        }
    }
}

void LMSController::listAllUsers()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    cout << "============USERS LIST==========" << endl;
    for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
    {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Username: " << (*iterator)->getUserName() << endl;
            cout << "Name: " << (*iterator)->getName() << endl;
            cout << "Role: " << (*iterator)->getRole() << endl;
            cout << "Status: " << (*iterator)->getStatus() << "\n" << endl;
    }
}

void LMSController::listStudentNames()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    cout << "============STUDENTS LIST==========" << endl;
    for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
    {
        if ((*iterator)->getRole() == "student" && (*iterator)->getStatus() != "inactive")
        {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Name: " << (*iterator)->getName() << "\n" << endl;
        }
    }
}

void LMSController::listCourses()
{
    cout << "==========COURSE LIST===========" << endl;
    for (vector<shared_ptr<Course>>::iterator iterator = m_courses.begin(); iterator != m_courses.end(); ++iterator)
    {
        cout << "Course id: C" << (*iterator)->getCourseId() << endl;
        cout << "Course title: " << (*iterator)->getCourseTitle() << endl;
        cout << "Course deadline: " << (*iterator)->getCourseDeadline() << endl;
        cout << "Total Number of Modules: " << (*iterator)->getTotalNumberOfModules() << "\n" << endl;
    }
}

void LMSController::listGroups()
{
    cout << "==========GROUPS LIST===========" << endl;
    for (vector<shared_ptr<Group>>::iterator iterator = m_groups.begin(); iterator != m_groups.end(); ++iterator)
    {
        cout << "Group id: G" << (*iterator)->getGroupId() << endl;
        cout << "Group Name: " << (*iterator)->getGroupName() << endl;
        cout << "Number of Students: " << (*iterator)->getStudentsInGroup().size() << "\n" << endl;
    }
}

void LMSController::enrollStudentToCourse()
{
    string userId, courseId;
    int convertedUserId = 0;
    int convertedCourseId = 0;
    cout << "============STUDENT ENROLLMENT==============\n";
    listStudentNames();
    cout << "Enter user id of student to enroll: ";
    cin >> userId;
    while (userId.length() < 2 || userId[0] != 'U' || isdigit(stoi(userId.substr(1))))
    {
        cout << "Invalid user id! Please Enter a valid user id: ";
        cin >> userId;
    }
    convertedUserId = stoi(userId.substr(1));
    listCourses();
    cout << "Enter course id of course to add to: ";
    cin >> courseId;
    while (courseId.length() < 2 || courseId[0] != 'C' || isdigit(stoi(courseId.substr(1))))
    {
        cout << "Invalid user id! Please Enter a valid user id: ";
        cin >> courseId;
    }
    convertedCourseId = stoi(courseId.substr(1));
    if (IsStudentEnrolledInCourse(convertedUserId, convertedCourseId))
    {
        cout << "Student is already enrolled in this course!" << endl;
        return;
    }

}

bool LMSController::IsStudentEnrolledInCourse(int studentId, int courseId)
{
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == studentId)
        {
            if ((*iterator)->getEnrolledCourseId() == courseId)
            {
                return true;
            }
        }
    }
    return false;
}

void LMSController::loadAllFiles()
{
    cout << "\nLoading datas from file........\n" << endl;
    if (!FileManager::loadIdsFromFile())
    {
        cout << "Failed to load ids from file!" << endl;
    }
    if (!FileManager::loadCoursesFromFile(m_courses))
    {
        cout << "Failed to load courses from file!" << endl;
    }
}

void LMSController::saveAllFiles()
{
    cout << "\nSaving datas to file........\n" << endl;
    if (!FileManager::saveIdsToFile())
    {
        cout << "Failed to write ids to file!" << endl;
    }
    if (!FileManager::saveCoursesToFile(m_courses))
    {
        cout << "Failed to write ids to file!" << endl;
    }
}
