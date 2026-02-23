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
                if ((*iterator)->getStatus() == "active")
                {
                    cout << "Course already exists!\n";
                    isExisting = true;
                    break;
                }
                else
                {
                    //reactivate course
                    (*iterator)->setStatus("active");
                    updateCourseDetails(*iterator);
                    cout << "Course reactivated successfully!\n" << endl;
                    return;
                }
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
    Authentication& authentication = Authentication::getInstance();
    string userId;
    int convertedUserId = 0;
    listStudentNames();
    if (getNumberOfStudents() == 0)
    {
        cout << "No students available!\n";
        return;
    }
    cout << "Enter user id of student to enroll: ";
    cin >> userId;
    cin.ignore(10000, '\n');
    while (userId.length() < 2 || userId[0] != 'U' || !all_of(userId.begin() + 1, userId.end(), ::isdigit))
    {
        cout << "Invalid user id! Please Enter a valid user id: ";
        cin >> userId;
        cin.ignore(10000, '\n');
    }
    convertedUserId = stoi(userId.substr(1));
    if (getStudentPendingEnrollmentsCount(convertedUserId) > 0)
    {
        cout << "Student cannot be removed! Student still has pending courses\n" << endl;
    }
    else
    {
        authentication.deleteUser(convertedUserId);
    }
}

void LMSController::removeInstructor()
{
    Authentication& authentication = Authentication::getInstance();
    std::string userId;
    int id;
    listInstructors();
    cout << "Enter user id of instructor to delete: ";
    cin >> userId;
    while (userId.length() < 2 || userId[0] != 'U' || !all_of(userId.begin() + 1, userId.end(), ::isdigit))
    {
        cout << "Invalid user id! Please Enter a valid user id: ";
        cin >> userId;
    }
    id = stoi(userId.substr(1));
    authentication.deleteUser(id);
}

void LMSController::removeAdministrator()
{
    Authentication& authentication = Authentication::getInstance();
    std::string userIdString;
    int userId;
    int currentUserId = m_user->getId();
    listAdminstrators();
    cout << "Enter user id of administrator to delete: ";
    cin >> userIdString;
    while (userIdString.length() < 2 || userIdString[0] != 'U' || !all_of(userIdString.begin() + 1, userIdString.end(), ::isdigit))
    {
        cout << "Invalid user id! Please Enter a valid user id: ";
        cin >> userIdString;
    }
    userId = stoi(userIdString.substr(1)); //from 1st index
    if (userId == currentUserId)
    {
        cout << "User cannot delete your own account!\n" << endl;
    }
    authentication.deleteUser(userId);
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
    cout << ">>>>>STUDENTS LIST<<<<<" << endl;
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
    cout << ">>>>>COURSE LIST<<<<<" << endl;
    for (vector<shared_ptr<Course>>::iterator iterator = m_courses.begin(); iterator != m_courses.end(); ++iterator)
    {
        if ((*iterator)->getStatus() != "inactive")
        {
            cout << "Course id: C" << (*iterator)->getCourseId() << endl;
            cout << "Course title: " << (*iterator)->getCourseTitle() << endl;
            cout << "Course deadline: " << (*iterator)->getCourseDeadline() << endl;
            cout << "Total Number of Modules: " << (*iterator)->getTotalNumberOfModules() << "\n";
            cout << "Course Status: " << (*iterator)->getStatus() << "\n" << endl;
        }
    }
}

void LMSController::listGroups()
{
    cout << ">>>>>GROUPS LIST<<<<<" << endl;
    for (vector<shared_ptr<Group>>::iterator iterator = m_groups.begin(); iterator != m_groups.end(); ++iterator)
    {
        cout << "Group id: G" << (*iterator)->getGroupId() << endl;
        cout << "Group Name: " << (*iterator)->getGroupName() << endl;
        cout << "Number of Students: " << (*iterator)->getStudentsInGroup().size() << "\n" << endl;
    }
}

void LMSController::listStudentsInGroup()
{
    string groupId;
    int convertedGroupId = 0;
    listGroups();
    if (m_groups.empty())
    {
        cout << "No groups available!\n";
        return;
    }
    cout << "Enter group id of group to show students: ";
    cin >> groupId;
    while (groupId.length() < 2 || groupId[0] != 'G' || !all_of(groupId.begin() + 1, groupId.end(), ::isdigit))
    {
        cout << "Invalid group id! Please Enter a valid group id: ";
        cin >> groupId;
        cin.ignore(10000, '\n');
    }
    convertedGroupId = stoi(groupId.substr(1));
    shared_ptr<Group> group = getGroup(convertedGroupId);
    if (group == nullptr)
    {
        cout << "Group not found!\n";
        return;
    }
    const vector<User*>& students = group->getStudentsInGroup();
    if (students.size() == 0)
    {
        cout << "No Students available!\n" << endl;
        return;
    }
    for (vector<User*>::const_iterator iterator = students.begin(); iterator != students.end(); ++iterator)
    {
        if ((*iterator)->getStatus() != "inactive")
        {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Username: " << (*iterator)->getUserName() << endl;
            cout << "Name: " << (*iterator)->getName() << "\n" << endl;
        }
    }
}

void LMSController::listStudentsProgressInCourse()
{
    string courseId;
    int convertedCourseId = 0;
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to show students progress of: ";
    cin >> courseId;
    cin.ignore(10000, '\n');
    while (courseId.length() < 2 || courseId[0] != 'C' || !all_of(courseId.begin() + 1, courseId.end(), ::isdigit))
    {
        cout << "Invalid course id! Please Enter a valid course id: ";
        cin >> courseId;
        cin.ignore(10000, '\n');
    }
    convertedCourseId = stoi(courseId.substr(1));
    shared_ptr<Course> course = getCourse(convertedCourseId);
    if (!course)
    {
        cout << "Course not found!\n";
        return;
    }
    bool found = false;
    cout << "\nSTUDENT NAME\t\tPROGRESS\n" << endl;
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledCourseId() == convertedCourseId)
        {
            cout << (*iterator)->getEnrolledStudentName() << "\t\t" << (*iterator)->getProgress() << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No Students enrolled in this course!\n";
    }
    cout << endl;
}

void LMSController::listStudentsGradeInCourse()
{
    string courseId;
    int convertedCourseId = 0;
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to show student grades of: ";
    cin >> courseId;
    cin.ignore(10000, '\n');
    while (courseId.length() < 2 || courseId[0] != 'C' || !all_of(courseId.begin() + 1, courseId.end(), ::isdigit))
    {
        cout << "Invalid course id! Please Enter a valid course id: ";
        cin >> courseId;
        cin.ignore(10000, '\n');
    }
    convertedCourseId = stoi(courseId.substr(1));
    shared_ptr<Course> course = getCourse(convertedCourseId);
    if (!course)
    {
        cout << "Course not found!\n";
        return;
    }
    bool found = false;
    cout << "\nSTUDENT NAME\t\tGRADE\n" << endl;
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledCourseId() == convertedCourseId)
        {
            cout << (*iterator)->getEnrolledStudentName() << "\t\t" << (*iterator)->getGrade() << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No Students enrolled in this course!\n";
    }
    cout << endl;
}

void LMSController::listEnrolledCourses()
{
    bool found = false;
    cout << "\n============Enrolled Course List=============\n";
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == m_user->getId())
        {
            int courseId = (*iterator)->getEnrolledCourseId();
            shared_ptr<Course> course = getCourse(courseId);
            if (course == nullptr)
            {
                continue;
            }
            cout << "C" << course->getCourseId() << ". " << course->getCourseTitle() << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No Enrolled Courses Found!\n" << endl;
    }
    cout << endl;
}

std::shared_ptr<Course> LMSController::getCourse(int courseId)
{
    for (vector<shared_ptr<Course>>::iterator iterator = m_courses.begin(); iterator != m_courses.end(); ++iterator)
    {
        if ((*iterator)->getCourseId() == courseId)
        {
            return *iterator;
        }
    }
    return nullptr;
}

User* LMSController::getUser(int userId)
{
    Authentication& authentication = Authentication::getInstance();
    return authentication.getUser(userId);
}

std::shared_ptr<Group> LMSController::getGroup(int groupId)
{
    for (vector<shared_ptr<Group>>::iterator iterator = m_groups.begin(); iterator != m_groups.end(); ++iterator)
    {
        if ((*iterator)->getGroupId() == groupId)
        {
            return *iterator;
        }
    }
    return nullptr;
}

void LMSController::addGroup()
{
    string groupName, courseId;
    int convertedCourseId = 0;
    bool isExisting = true;
    cin.ignore(10000, '\n');
    while (isExisting)
    {
        cout << "Enter the group name: ";
        getline(cin, groupName);
        if (groupName.empty())
        {
            cout << "Title cannot be empty. Please try again.\n";
            continue;
        }
        isExisting = false;
        for (vector<shared_ptr<Group>>::iterator iterator = m_groups.begin(); iterator != m_groups.end(); ++iterator)
        {
            if ((*iterator)->getGroupName() == groupName)
            {
                cout << "Group already exists!\n";
                isExisting = true;
                break;
            }
        }
    }
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to add to: ";
    cin >> courseId;
    cin.ignore(10000, '\n');
    while (courseId.length() < 2 || courseId[0] != 'C' || !all_of(courseId.begin() + 1, courseId.end(), ::isdigit))
    {
        cout << "Invalid course id! Please Enter a valid course id: ";
        cin >> courseId;
        cin.ignore(10000, '\n');
    }
    convertedCourseId = stoi(courseId.substr(1));
    shared_ptr<Course> course = getCourse(convertedCourseId);
    if (course == nullptr)
    {
        cout << "Course not found!" << endl;
        return;
    }
    m_groups.push_back(make_shared<Group>(groupName, course));
    cout << "Group Added Successfully!" << endl;
}

void LMSController::removeCourse()
{
    string courseId;
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to remove: ";
    cin >> courseId;
    cin.ignore(10000, '\n');
    while (courseId.length() < 2 || courseId[0] != 'C' || !all_of(courseId.begin() + 1, courseId.end(), ::isdigit))
    {
        cout << "Invalid course id! Please Enter a valid course id: ";
        cin >> courseId;
        cin.ignore(10000, '\n');
    }
    int convertedCourseId = stoi(courseId.substr(1));
    int numberOfStudentsEnrolledInCourse = getNumberOfStudentsEnrolledInCourse(convertedCourseId);
    if (numberOfStudentsEnrolledInCourse > 0)
    {
        cout << "Course cant be removed as it has student enrollments!\n" << endl;
        return;
    }
    else
    {
        getCourse(convertedCourseId)->setStatus("inactive");
        cout << "Course removed successfully!\n" << endl;
    }
}

void LMSController::updateCourseDetails(shared_ptr<Course> course)
{
    string deadline;
    int numberOfModules = 0;
    while (deadline.empty())
    {
        cout << "Enter the new deadline: ";
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
    course->setCourseDeadline(deadline);
    course->setTotalNumberOfModules(numberOfModules);
    cout << "Course Updated Successfully!\n" << endl;
}

void LMSController::removeGroup()
{
    string groupId;
    int convertedGroupId = 0;
    listGroups();
    if (m_groups.empty())
    {
        cout << "No groups available!\n";
        return;
    }
    cout << "Enter group id of group to remove: ";
    cin >> groupId;
    while (groupId.length() < 2 || groupId[0] != 'G' || !all_of(groupId.begin() + 1, groupId.end(), ::isdigit))
    {
        cout << "Invalid group id! Please Enter a valid group id: ";
        cin >> groupId;
        cin.ignore(10000, '\n');
    }
    convertedGroupId = stoi(groupId.substr(1));
    shared_ptr<Group> group = getGroup(convertedGroupId);
    if (group == nullptr)
    {
        cout << "Group not found!\n";
        return;
    }
    if (group->getCountOfStudentsInGroup() > 0)
    {
        cout << "Group cannot be removed! Contains enrolled students\n" << endl;
        return;
    }
    for (vector<shared_ptr<Group>>::iterator iterator = m_groups.begin(); iterator != m_groups.end(); ++iterator)
    {
        if ((*iterator)->getGroupId() == convertedGroupId)
        {
            m_groups.erase(iterator);
            break;
        }
    }
    cout << "Group deleted successfully!\n" << endl;
}

void LMSController::enrollStudentToCourse()
{
    string userId, courseId;
    int convertedUserId = 0;
    int convertedCourseId = 0;
    cout << "============STUDENT ENROLLMENT==============\n";
    listStudentNames();
    if (getNumberOfStudents() == 0)
    {
        cout << "No students available!\n";
        return;
    }
    cout << "Enter user id of student to enroll: ";
    cin >> userId;
    cin.ignore(10000, '\n');
    while (userId.length() < 2 || userId[0] != 'U' || !all_of(userId.begin() + 1, userId.end(), ::isdigit))
    {
        cout << "Invalid user id! Please Enter a valid user id: ";
        cin >> userId;
        cin.ignore(10000, '\n');
    }
    convertedUserId = stoi(userId.substr(1));
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to add to: ";
    cin >> courseId;
    cin.ignore(10000, '\n');
    while (courseId.length() < 2 || courseId[0] != 'C' || !all_of(courseId.begin() + 1, courseId.end(), ::isdigit))
    {
        cout << "Invalid course id! Please Enter a valid course id: ";
        cin >> courseId;
        cin.ignore(10000, '\n');
    }
    convertedCourseId = stoi(courseId.substr(1));
    if (IsStudentEnrolledInCourse(convertedUserId, convertedCourseId))
    {
        cout << "Student is already enrolled in this course!\n";
        return;
    }
    User* student = getUser(convertedUserId);
    shared_ptr<Course> course = getCourse(convertedCourseId);
    if (!student)
    {
        cout << "Student not found!\n";
        return;
    }
    if (!course)
    {
        cout << "Course not found!\n";
        return;
    }
    m_enrollments.push_back(make_shared<Enrollment>(student, course, 0, 0, "NIL", nullptr));
    cout << "Student Enrolled Successfully!\n" << endl;
}

void LMSController::enrollStudentToGroup()
{
    string userId, groupId;
    int convertedUserId = 0;
    int convertedGroupId = 0;
    cout << "============GROUP ENROLLMENT==============\n";
    listStudents();
    if (getNumberOfStudents() == 0)
    {
        cout << "No Students available!" << endl;
        return;
    }
    cout << "Enter user id of student to enroll: ";
    cin >> userId;
    while (userId.length() < 2 || userId[0] != 'U' || !all_of(userId.begin() + 1, userId.end(), ::isdigit))
    {
        cout << "Invalid user id! Please Enter a valid user id: ";
        cin >> userId;
    }
    convertedUserId = stoi(userId.substr(1));
    listGroups();
    if (m_groups.size() == 0)
    {
        cout << "No Groups available!" << endl;
        return;
    }
    cout << "Enter group id of group to enroll to: ";
    cin >> groupId;
    while (groupId.length() < 2 || groupId[0] != 'G' || !all_of(groupId.begin() + 1, groupId.end(), ::isdigit))
    {
        cout << "Invalid group id! Please Enter a valid group id: ";
        cin >> groupId;
    }
    convertedGroupId = stoi(groupId.substr(1));
    //checks if student is already enrolled in group
    if (IsStudentEnrolledInGroup(convertedUserId, convertedGroupId))
    {
        cout << "Student is already enrolled in this group!" << endl;
        return;
    }
    //checks if student is enrolled in groups course but not group
    shared_ptr<Group> group = getGroup(convertedGroupId);
    if (group == nullptr)
    {
        cout << "Group Not Found" << endl;
        return;
    }
    int groupCourseId = group->getGroupCourseId();
    if (IsStudentEnrolledInGroupsCourse(convertedUserId, convertedGroupId))
    {
        for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
        {
            if ((*iterator)->getEnrolledStudentId() == convertedUserId && (*iterator)->getEnrolledCourseId() == groupCourseId && (*iterator)->getEnrolledGroupId() == -1)
            {
                (*iterator)->setGroup(group);
                group->addStudentToGroup(getUser(convertedUserId));
            }
        }
        cout << "Student is already enrolled to course! Added student to course group" << endl;
        return;
    }
    //fresh enrollment
    User* user = getUser(convertedUserId);
    shared_ptr<Course> course = getCourse(groupCourseId);

    if (!user || !course)
    {
        cout << "Enrollment failed due to invalid data." << endl;
        return;
    }
    m_enrollments.push_back(make_shared<Enrollment>(user, course, 0, 0, "NIL", group));
    group->addStudentToGroup(user);
    cout << "Student enrolled to group successfully!\n" << endl;
}

void LMSController::enrollToCourse()
{
    string courseId;
    int studentId = m_user->getId();
    int convertedCourseId = 0;
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to add to: ";
    cin >> courseId;
    cin.ignore(10000, '\n');
    while (courseId.length() < 2 || courseId[0] != 'C' || !all_of(courseId.begin() + 1, courseId.end(), ::isdigit))
    {
        cout << "Invalid course id! Please Enter a valid course id: ";
        cin >> courseId;
        cin.ignore(10000, '\n');
    }
    convertedCourseId = stoi(courseId.substr(1));
    if (IsStudentEnrolledInCourse(studentId, convertedCourseId))
    {
        cout << "You are already enrolled in this course!\n";
        return;
    }
    shared_ptr<Course> course = getCourse(convertedCourseId);
    if (!course)
    {
        cout << "Course not found!\n";
        return;
    }
    m_enrollments.push_back(make_shared<Enrollment>(m_user, course, 0, 0, "NIL", nullptr));
    cout << "Enrolled to course " << course->getCourseTitle() << " successfully!\n" << endl;
}

int LMSController::getNumberOfStudents()
{
    int studentCount = 0;
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
    {
        if ((*iterator)->getRole() == "student" && (*iterator)->getStatus() != "inactive")
        {
            studentCount++;
        }
    }
    return studentCount;
}

int LMSController::getNumberOfStudentsEnrolledInCourse(int courseId)
{
    int enrollmentCount = 0;
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledCourseId() == courseId)
        {
            enrollmentCount++;
        }
    }
    return enrollmentCount;
}

int LMSController::getStudentEnrollmentsCount(int studentId)
{
    int enrollmentCount = 0;
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == studentId)
        {
            enrollmentCount++;
        }
    }
    return enrollmentCount;
}

int LMSController::getStudentPendingEnrollmentsCount(int studentId)
{
    int pendingEnrollmentCount = 0;
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == studentId)
        {
            if ((*iterator)->getProgress() < 100)
            {
                pendingEnrollmentCount++;
            }

        }
    }
    return pendingEnrollmentCount;
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

bool LMSController::IsStudentEnrolledInGroup(int studentId, int groupId)
{
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == studentId)
        {
            if ((*iterator)->getEnrolledGroupId() != -1)
            {
                if ((*iterator)->getEnrolledGroupId() == groupId)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool LMSController::IsStudentEnrolledInGroupsCourse(int studentId, int groupId)
{
    shared_ptr<Group> group = getGroup(groupId);
    if (group == nullptr)
    {
        return false;
    }
    int groupCourseId = group->getGroupCourseId();
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == studentId)
        {
            if ((*iterator)->getEnrolledGroupId() == -1)
            {
                if ((*iterator)->getEnrolledCourseId() == groupCourseId)
                {
                    return true;
                }
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
    if (!FileManager::loadGroupsFromFile(m_groups, *this))
    {
        cout << "Failed to load groups from file!" << endl;
    }
    if (!FileManager::loadEnrollmentsFromFile(m_enrollments, *this))
    {
        cout << "Failed to load enrollments from file!" << endl;
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
    if (!FileManager::saveGroupsToFile(m_groups))
    {
        cout << "Failed to write groups to file!" << endl;
    }
    if (!FileManager::saveEnrollmentsToFile(m_enrollments))
    {
        cout << "Failed to write enrollments to file!" << endl;
    }
}
