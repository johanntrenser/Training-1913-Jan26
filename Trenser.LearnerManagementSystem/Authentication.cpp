#include "Authentication.h"
using namespace std;

User* Authentication::login()
{
    cout << "================LOGIN====================" << endl;
    string username = "";
    string password = "";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    if (username.empty() || password.empty())
    {
        cout << "Username or Password cannot be empty!" << endl;
        return nullptr;
    }
    for (vector<User*>::iterator iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
    {
        if (((*iterator)->getUserName() == username) && ((*iterator)->getPassword() == password) && ((*iterator)->getStatus() != "inactive"))
        {
            return *iterator;
        }
    }
    return nullptr;
}

std::string Authentication::registerUser()
{
    cout << "================REGISTER USER====================" << endl;
    string username = "";
    string password = "";
    string name = "";
    string statusMessage = "";
    int choice = 0;
    cout << "Enter the username: ";
    cin >> username;
    for (vector<User*>::iterator iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
    {
        if (((*iterator)->getUserName() == username))
        {
            statusMessage = "Username already exists!";
            return statusMessage;
        }
    }
    cout << "Enter your password: ";
    cin >> password;
    cin.ignore(10000, '\n');
    cout << "Enter name: ";
    getline(cin, name);
    while (name.empty())
    {
        cout << "Name cannot be empty! Please Enter name again: ";
        getline(cin, name);
    }
    cout << "Select Role:\n1.Student\n2.Instructor\nEnter role (1 - 2): ";
    cin >> choice;
    while (choice < 1 || choice > 2)
    {
        cout << "Invalid choice! Please select 1 or 2: " << endl;
        cin >> choice;
    }
    if (choice == 1)
    {
        m_users.push_back(new Student(username, name, password));
    }
    else if (choice == 2)
    {
        m_users.push_back(new Instructor(username, name, password));
    }
    statusMessage = "Registration successfull!";
    return statusMessage;
}

void Authentication::addUser(User* user)
{
    m_users.push_back(user);
}

void Authentication::deleteUser(int userId)
{
    for (vector<User*>::iterator iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
    {
        if (((*iterator)->getId() == userId))
        {
            if ((*iterator)->getId() == 1 || (*iterator)->getUserName() == "admin")
            {
                cout << "User doesnt have the access to delete this administrator user!" << endl;
                return;
            }
            else
            {
                (*iterator)->setStatus("inactive");
            }
        }
    }
    cout << "User has been deleted!\n" << endl;
}

User* Authentication::getUser(int userId)
{
    for (vector<User*>::iterator iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
    {
        if ((*iterator)->getId() == userId)
        {
            return *iterator;
        }
    }
    return nullptr;
}

const vector<User*>& Authentication::getUsers() const
{
    return m_users;
}


bool Authentication::loadUsersFromFile()
{
    ifstream fileReader(FileManager::m_userFilePath, ios::in);
    if (!fileReader.is_open())
    {
        return false;
    }
    fileReader.clear();
    fileReader.seekg(0, ios::beg);
    bool skipHeader = true;
    string currentLine;
    while (getline(fileReader, currentLine))
    {
        if (skipHeader)
        {
            skipHeader = false;
            continue;
        }
        stringstream currentUser(currentLine);
        string id, username, name, password, role, status;
        getline(currentUser, id, ',');
        getline(currentUser, username, ',');
        getline(currentUser, name, ',');
        getline(currentUser, password, ',');
        getline(currentUser, role, ',');
        getline(currentUser, status, ',');
        if (role == "admin")
        {
            m_users.push_back(new Admin(stoi(id), username, name, password, role, status));
        }
        else if (role == "student")
        {
            m_users.push_back(new Student(stoi(id), username, name, password, role, status));
        }
        else if (role == "instructor")
        {
            m_users.push_back(new Instructor(stoi(id), username, name, password, role, status));
        }
    }
    fileReader.close();
    return true;
}

bool Authentication::saveUsersToFile()
{
    ofstream fileWriter(FileManager::m_userFilePath, ios::out | ios::trunc);
    if (!fileWriter.is_open())
    {
        return false;
    }
    fileWriter << "ID,USERNAME,NAME,PASSWORD,ROLE,STATUS" << endl;
    for (vector<User*>::iterator iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
    {
        fileWriter << (*iterator)->getId() << "," << (*iterator)->getUserName() << "," << (*iterator)->getName() << "," << (*iterator)->getPassword() << ","
            << (*iterator)->getRole() << "," << (*iterator)->getStatus();
        fileWriter << endl;
    } 
    fileWriter.close();
    return true;
}

Authentication& Authentication::getInstance()
{
    static Authentication instance;
    return instance;
}
