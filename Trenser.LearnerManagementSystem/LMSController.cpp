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
                if ((*iterator)->getStatus())
                {
                    cout << "Course already exists!\n";
                    isExisting = true;
                    break;
                }
                else
                {
                    //reactivate course
                    (*iterator)->setStatus(true);
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
    username = getUniqueUsername();
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
    username = getUniqueUsername();
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
    name = getUniqueUsername();
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
    int userId = 0;
    listStudentNames();
    if (getNumberOfStudents() == 0)
    {
        cout << "No students available!\n";
        return;
    }
    cout << "Enter user id of student to delete: ";
    userId = getValidatedUserId();
    User* user = getUser(userId);
    if (!user || user->getRole() != Student::STUDENT_ROLE || !user->getStatus())
    {
        cout << "Student not found!\n";
        return;
    }
    if (getStudentPendingEnrollmentsCount(userId) > 0)
    {
        cout << "Student cannot be removed! Student still has pending courses\n" << endl;
    }
    else
    {
        authentication.deleteUser(userId);
    }
}

void LMSController::removeInstructor()
{
    Authentication& authentication = Authentication::getInstance();
    int userId;
    int id;
    listInstructors();
    if (getNumberOfInstructors() == 0)
    {
        cout << "No instructors available!\n";
        return;
    }
    cout << "Enter user id of instructor to delete: ";
    userId = getValidatedUserId();
    User* user = getUser(userId);
    if (!user ||  user->getRole() != Instructor::INSTRUCTOR_ROLE || !user->getStatus())
    {
        cout << "Instructor not found!\n";
        return;
    }
    authentication.deleteUser(userId);
}

void LMSController::removeAdministrator()
{
    Authentication& authentication = Authentication::getInstance();
    int userId;
    int currentUserId = m_user->getId();
    listAdminstrators();
    cout << "Enter user id of administrator to delete: ";
    userId = getValidatedUserId();
    if (userId == currentUserId)
    {
        cout << "User cannot delete your own account!\n" << endl;
        return;
    }
    User* user = getUser(userId);
    if (!user || user->getRole() != Admin::ADMINISTRATOR_ROLE || !user->getStatus())
    {
        cout << "Administrator not found!\n";
        return;
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
        if ((*iterator)->getRole() == Student::STUDENT_ROLE && (*iterator)->getStatus())
        {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Username: " << (*iterator)->getUserName() << endl;
            cout << "Name: " << (*iterator)->getName() << endl;
            cout << "Role: " << (*iterator)->getRole() << endl;
            cout << "Status: " << ((*iterator)->getStatus() ? "active" : "inactive") << "\n" << endl;
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
        if ((*iterator)->getRole() == Admin::ADMINISTRATOR_ROLE && (*iterator)->getStatus())
        {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Username: " << (*iterator)->getUserName() << endl;
            cout << "Name: " << (*iterator)->getName() << endl;
            cout << "Role: " << (*iterator)->getRole() << endl;
            cout << "Status: " << ((*iterator)->getStatus() ? "active" : "inactive") << "\n" << endl;
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
        if ((*iterator)->getRole() == Instructor::INSTRUCTOR_ROLE && (*iterator)->getStatus())
        {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Username: " << (*iterator)->getUserName() << endl;
            cout << "Name: " << (*iterator)->getName() << endl;
            cout << "Role: " << (*iterator)->getRole() << endl;
            cout << "Status: " << ((*iterator)->getStatus() ? "active" : "inactive") << "\n" << endl;
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
        cout << "Status: " << ((*iterator)->getStatus() ? "active" : "inactive") << "\n" << endl;
    }
}

void LMSController::listStudentNames()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    cout << ">>>>>STUDENTS LIST<<<<<" << endl;
    for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
    {
        if ((*iterator)->getRole() == Student::STUDENT_ROLE && (*iterator)->getStatus())
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
        if ((*iterator)->getStatus())
        {
            cout << "Course id: C" << (*iterator)->getCourseId() << endl;
            cout << "Course title: " << (*iterator)->getCourseTitle() << endl;
            cout << "Course deadline: " << (*iterator)->getCourseDeadline() << endl;
            cout << "Total Number of Modules: " << (*iterator)->getTotalNumberOfModules() << "\n";
            cout << "Course Status: " << ((*iterator)->getStatus()? "active" : "inactive") << "\n" << endl;
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
    int groupId = 0;
    listGroups();
    if (m_groups.empty())
    {
        cout << "No groups available!\n";
        return;
    }
    cout << "Enter group id of group to show students: ";
    groupId = getValidatedGroupId();
    shared_ptr<Group> group = getGroup(groupId);
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
        if ((*iterator)->getStatus())
        {
            cout << "User id: U" << (*iterator)->getId() << endl;
            cout << "Username: " << (*iterator)->getUserName() << endl;
            cout << "Name: " << (*iterator)->getName() << "\n" << endl;
        }
    }
}

void LMSController::listStudentsProgressInCourse()
{
    int courseId = 0;
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to show students progress of: ";
    courseId = getValidatedCourseId();
    shared_ptr<Course> course = getCourse(courseId);
    if (!course)
    {
        cout << "Course not found!\n";
        return;
    }
    bool found = false;
    cout << "\n============STUDENTS PROGRESS\n" << endl;
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledCourseId() == courseId)
        {
            cout << "Student Name: " << (*iterator)->getEnrolledStudentName() << endl;
            cout << "Progress: " << (*iterator)->getProgress() << "\n" << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No Students enrolled in this course!\n";
    }
    cout << "\n" << endl;
}

void LMSController::listStudentsGradeInCourse()
{
    int courseId = 0;
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to show student grades of: ";
    courseId = getValidatedCourseId();
    shared_ptr<Course> course = getCourse(courseId);
    if (!course)
    {
        cout << "Course not found!\n";
        return;
    }
    bool found = false;
    cout << "\n================STUDENTS GRADE===========\n\n";
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledCourseId() == courseId)
        {
            cout << "Student Name: " << (*iterator)->getEnrolledStudentName() << endl;
            cout << "Grade: " << (*iterator)->getGrade() << "\n" <<endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No Students enrolled in this course!\n";
    }
    cout << "\n" << endl;
}

void LMSController::listStudentGrades()
{
    bool found = false;
    cout << "\n===============STUDENT COURSE GRADES============" << endl;
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == m_user->getId())
        {
            shared_ptr<Course> course = getCourse((*iterator)->getEnrolledCourseId());
            if (course == nullptr)
            {
                continue;
            }
            cout << "Name: " << (*iterator)->getEnrolledStudentName() << endl;
            cout << "Course: " << course->getCourseTitle() << endl;
            cout << "Grade: " << (*iterator)->getGrade() << "\n" << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "Student has no course enrollments!\n";
    }
    cout << "\n" << endl;
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

void LMSController::listEnrolledGroups()
{
    bool found = false;
    cout << "\n============Enrolled Groups List=============\n";
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == m_user->getId())
        {
            int groupId = (*iterator)->getEnrolledGroupId();
            if (groupId == -1)
            {
                continue;
            }
            else
            {
                shared_ptr<Group> group = getGroup(groupId);
                if (group != nullptr)
                {
                    cout << "G" << group->getGroupId() << ". " << group->getGroupName() << endl;
                    found = true;
                }
            }
        }
    }
    if (!found)
    {
        cout << "No Enrolled Groups Found!\n" << endl;
    }
    cout << endl;
}

void LMSController::listStudentProgress()
{
    bool found = false;
    cout << "\n============Enrolled Courses Student Progress=======\n";
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == m_user->getId())
        {
            found = true;
            shared_ptr<Course> course = getCourse((*iterator)->getEnrolledCourseId());
            if (course != nullptr)
            {
                cout << "Student Name: " << (*iterator)->getEnrolledStudentName() << endl;
                cout << "Course Name: " << course->getCourseTitle() << endl;
                cout << "Progress: " << (*iterator)->getProgress() << "%\t\n" << endl;
            }
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
    string groupName;
    int courseId = 0;
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
    courseId = getValidatedCourseId();
    shared_ptr<Course> course = getCourse(courseId);
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
    int courseId = 0;
    int numberOfStudentsEnrolledInCourse = 0;
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to remove: ";
    
    courseId = getValidatedCourseId();
    numberOfStudentsEnrolledInCourse = getNumberOfStudentsEnrolledInCourse(courseId);
    if (numberOfStudentsEnrolledInCourse > 0)
    {
        cout << "Course cant be removed as it has student enrollments!\n" << endl;
        return;
    }
    else
    {
        shared_ptr<Course> course = getCourse(courseId);
        if (course == nullptr)
        {
            cout << "Course not found!\n";
            return;
        }
        course->setStatus(false);
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
    int groupId = 0;
    listGroups();
    if (m_groups.empty())
    {
        cout << "No groups available!\n";
        return;
    }
    cout << "Enter group id of group to remove: ";
    groupId = getValidatedGroupId();
    shared_ptr<Group> group = getGroup(groupId);
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
        if ((*iterator)->getGroupId() == groupId)
        {
            m_groups.erase(iterator);
            break;
        }
    }
    cout << "Group deleted successfully!\n" << endl;
}

void LMSController::enrollStudentToCourse()
{
    int userId = 0;
    int courseId = 0;
    cout << "============STUDENT ENROLLMENT==============\n";
    listStudentNames();
    if (getNumberOfStudents() == 0)
    {
        cout << "No students available!\n";
        return;
    }
    cout << "Enter user id of student to enroll: ";
    userId = getValidatedUserId();
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to add to: ";
    courseId = getValidatedCourseId();
    if (IsStudentEnrolledInCourse(userId, courseId))
    {
        cout << "Student is already enrolled in this course!\n";
        return;
    }
    User* student = getUser(userId);
    if (!student || student->getRole() != Student::STUDENT_ROLE || !student->getStatus())
    {
        cout << "Student not found!\n";
        return;
    }
    shared_ptr<Course> course = getCourse(courseId);
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
    int userId = 0;
    int groupId = 0;
    cout << "============GROUP ENROLLMENT==============\n";
    listStudents();
    if (getNumberOfStudents() == 0)
    {
        cout << "No Students available!" << endl;
        return;
    }
    cout << "Enter user id of student to enroll: ";
    userId = getValidatedUserId();
    listGroups();
    if (m_groups.size() == 0)
    {
        cout << "No Groups available!" << endl;
        return;
    }
    cout << "Enter group id of group to enroll to: ";
    groupId = getValidatedGroupId();
    //checks if student is already enrolled in group
    if (IsStudentEnrolledInGroup(userId, groupId))
    {
        cout << "Student is already enrolled in this group!" << endl;
        return;
    }
    //checks if student is enrolled in groups course but not group
    shared_ptr<Group> group = getGroup(groupId);
    if (group == nullptr)
    {
        cout << "Group Not Found" << endl;
        return;
    }
    int groupCourseId = group->getGroupCourseId();
    if (IsStudentEnrolledInGroupsCourse(userId, groupId))
    {
        for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
        {
            if ((*iterator)->getEnrolledStudentId() == userId && (*iterator)->getEnrolledCourseId() == groupCourseId && (*iterator)->getEnrolledGroupId() == -1)
            {
                (*iterator)->setGroup(group);
                group->addStudentToGroup(getUser(userId));
            }
        }
        cout << "Student is already enrolled to course! Added student to course group" << endl;
        return;
    }
    //fresh enrollment
    User* user = getUser(userId);
    shared_ptr<Course> course = getCourse(groupCourseId);
    if (!user || user->getRole() != Student::STUDENT_ROLE || !user->getStatus())
    {
        cout << "Student not found!" << endl;
        return;
    }
    if (!course)
    {
        cout << "Course not found!" << endl;
        return;
    }
    m_enrollments.push_back(make_shared<Enrollment>(user, course, 0, 0, "NIL", group));
    group->addStudentToGroup(user);
    cout << "Student enrolled to group successfully!\n" << endl;
}

void LMSController::enrollToCourse()
{
    int courseId = 0;
    int studentId = m_user->getId();
    listCourses();
    if (m_courses.empty())
    {
        cout << "No courses available!\n";
        return;
    }
    cout << "Enter course id of course to add to: ";
    courseId = getValidatedCourseId();
    if (IsStudentEnrolledInCourse(studentId, courseId))
    {
        cout << "You are already enrolled in this course!\n";
        return;
    }
    shared_ptr<Course> course = getCourse(courseId);
    if (!course)
    {
        cout << "Course not found!\n";
        return;
    }
    m_enrollments.push_back(make_shared<Enrollment>(m_user, course, 0, 0, "NIL", nullptr));
    cout << "Enrolled to course " << course->getCourseTitle() << " successfully!\n" << endl;
}

void LMSController::completeModule()
{
    int courseId = 0;
    int studentId = m_user->getId();
    listEnrolledCourses();
    cout << "Enter course id to complete a module: ";
    courseId = getValidatedCourseId();
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == studentId && (*iterator)->getEnrolledCourseId() == courseId)
        {
            shared_ptr<Course> course = getCourse(courseId);
            if (!course)
            {
                cout << "Course not found!\n";
                return;
            }
            int completedNumberOfModules = (*iterator)->getNumberOfCompletedModules();
            if (completedNumberOfModules >= course->getTotalNumberOfModules())
            {
                cout << "All Modules already completed!\n" << endl;
                return;
            }
            completedNumberOfModules++;
            (*iterator)->setNumberOfCompletedModules(completedNumberOfModules);
            int progress = (completedNumberOfModules * 100) / course->getTotalNumberOfModules();
            (*iterator)->setProgress(progress);
            cout << "Module completed successfully!\n";
            cout << "Current Progress: " << progress << "%\n\n";
            return;
        }
    }
    cout << "Enrollment not found!\n" << endl;
}

void LMSController::gradeStudent()
{
    int courseId = 0, userId = 0;
    listCourses();
    cout << "Enter course id: ";
    courseId = getValidatedCourseId();
    shared_ptr<Course> course = getCourse(courseId);
    if (course == nullptr)
    {
        cout << "Course not found!\n" << endl;
        return;
    }
    bool studentFound = false;
    cout << "\nStudents in this course:\n";
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledCourseId() == courseId)
        {
            cout << "U" << (*iterator)->getEnrolledStudentId() << " - " << (*iterator)->getEnrolledStudentName() << endl;
            studentFound = true;
        }
    }
    if (!studentFound)
    {
        cout << "No students enrolled in this course!\n" << endl;
        return;
    }
    cout << "\nEnter student id to grade: ";
    userId = getValidatedUserId();
    for (vector<shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == userId && (*iterator)->getEnrolledCourseId() == courseId)
        {
            if ((*iterator)->getProgress() < 100)
            {
                cout << "Student has not completed course yet!\n" << endl;
                return;
            }
            string grade = getValidatedGrade();
            (*iterator)->setGrade(grade);
            cout << "Grade assigned successfully!\n" << endl;
            return;
        }
    }
    cout << "Enrollment not Found!\n" << endl;
}

int LMSController::getNumberOfStudents()
{
    int studentCount = 0;
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
    {
        if ((*iterator)->getRole() == Student::STUDENT_ROLE && (*iterator)->getStatus())
        {
            studentCount++;
        }
    }
    return studentCount;
}

int LMSController::getNumberOfInstructors()
{
    int instructorCount = 0;
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    for (vector<User*>::iterator iterator = users.begin(); iterator != users.end(); ++iterator)
    {
        if ((*iterator)->getRole() == Instructor::INSTRUCTOR_ROLE && (*iterator)->getStatus())
        {
            instructorCount++;
        }
    }
    return instructorCount;
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

void LMSController::viewStudentsInMyGroup()
{
    int studentId = m_user->getId();
    bool found = false;
    for (std::vector<std::shared_ptr<Enrollment>>::iterator iterator = m_enrollments.begin(); iterator != m_enrollments.end(); ++iterator)
    {
        if ((*iterator)->getEnrolledStudentId() == studentId)
        {
            int groupId = (*iterator)->getEnrolledGroupId();
            if (groupId != -1)
            {
                std::shared_ptr<Group> group = getGroup(groupId);
                if (group != nullptr)
                {
                    cout << "\nGroup: " << group->getGroupName() << endl;
                    cout << "Students in group:\n";
                    const std::vector<User*>& students = group->getStudentsInGroup();
                    for (std::vector<User*>::const_iterator studentIterator = students.begin(); studentIterator != students.end(); ++studentIterator)
                    {
                        User* student = *studentIterator;
                        if (student != nullptr && student->getStatus())
                        {
                            cout << "U" << student->getId() << " - " << student->getName() << endl;
                        }
                    }
                    found = true;
                }
            }
        }
    }
    if (!found)
    {
        cout << "You are not enrolled in any group!\n" << endl;
    }
    cout << endl;
}

std::string LMSController::getValidatedGrade()
{
    std::string inputGrade;
    while (true)
    {
        cout << "Enter grade (A - F): ";
        cin >> inputGrade;
        if (inputGrade.length() != 1)
        {
            cout << "Invalid grade! Please enter a single letter (A - F).\n";
            continue;
        }
        inputGrade[0] = toupper(inputGrade[0]);
        if (inputGrade[0] >= 'A' && inputGrade[0] <= 'F')
        {
            return inputGrade;
        }
        cout << "Invalid grade! Please enter between A and F.\n";
    }
}

int LMSController::getValidatedUserId()
{
    string userId;
    while (true)
    {
        cin >> userId;
        cin.ignore(10000, '\n');
        if (userId.length() < 2 || userId[0] != 'U' || !all_of(userId.begin() + 1, userId.end(), ::isdigit))
        {
            cout << "Invalid user id! Please enter a valid user id (Format: U123): ";
            continue;
        }
        try
        {
            return stoi(userId.substr(1));
        }
        catch (const std::exception&)
        {
            cout << "Could not convert userId to integer! Please enter a valid id: ";
        }
    }
}

int LMSController::getValidatedGroupId()
{
    string groupId;
    while (true)
    {
        cin >> groupId;
        cin.ignore(10000, '\n');
        if(groupId.length() < 2 || groupId[0] != 'G' || !all_of(groupId.begin() + 1, groupId.end(), ::isdigit))
        {
            cout << "Invalid group id! Please Enter a valid group id (Format: G123): ";
            continue;
        }
        try
        {
            return stoi(groupId.substr(1));
        }
        catch (const std::exception&)
        {
            cout << "Could not convert groupId to integer! Please enter a valid id: ";
        }
    }
}

int LMSController::getValidatedCourseId()
{
    string courseId;
    while (true)
    {
        cin >> courseId;
        cin.ignore(10000, '\n');
        if (courseId.length() < 2 || courseId[0] != 'C' || !all_of(courseId.begin() + 1, courseId.end(), ::isdigit))
        {
            cout << "Invalid course id! Please Enter a valid course id: ";
            continue;
        }
        try
        {
            return stoi(courseId.substr(1));
        }
        catch (const std::exception&)
        {
            cout << "Could not convert courseId to integer! Please enter a valid id: ";
        }
    }
}

std::string LMSController::getUniqueUsername()
{
    Authentication& authentication = Authentication::getInstance();
    vector<User*> users = authentication.getUsers();
    string username = "";
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
    return username;
}

void LMSController::loadAllFiles()
{
    cout << "\nLoading datas from file........\n" << endl;
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
    if (!FileManager::saveCoursesToFile(m_courses))
    {
        cout << "Failed to write courses to file!" << endl;
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
