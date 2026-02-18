#include "Authentication.h"
using namespace std;

User* Authentication::login()
{
    string username = "";
    string password = "";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    if (username.empty() || password.empty())
    {
        cout << "Username or Password cannot be empty!" << endl;
        return nullptr;
    }
    for (vector<User*>::iterator iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
    {
        if (((*iterator)->getUserName() == username) && ((*iterator)->getPassword() == password))
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
    string statusMessage = "";
    int choice = 0;
    cout << "Enter the username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    for (vector<User*>::iterator iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
    {
        if (((*iterator)->getUserName() == username))
        {
            statusMessage = "Username already exists!";
            return statusMessage;
        }
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
        m_users.emplace_back(Student(username, password));
    }
    else if (choice == 2)
    {
        m_users.emplace_back(Instructor(username, password));
    }
    statusMessage = "Registration successfull!";
    return statusMessage;
}
