
#include "../include/Member.h"
#include <iostream>

using namespace std;

// Default constructor
Member::Member()
{
    memberId = "";
    name = "";
    email = "";
    phone = "";
}

// Parameterized constructor
Member::Member(string id, string memberName,
               string memberEmail, string memberPhone)
{
    memberId = id;
    name = memberName;
    email = memberEmail;
    phone = memberPhone;
}

// Display member details
void Member::displayMember() const
{
    cout << "Member ID: " << memberId << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
}

// Getter functions
string Member::getMemberId() const
{
    return memberId;
}

string Member::getName() const
{
    return name;
}

string Member::getEmail() const
{
    return email;
}

string Member::getPhone() const
{
    return phone;
}

// Setter functions
void Member::setName(string newName)
{
    name = newName;
}

void Member::setEmail(string newEmail)
{
    email = newEmail;
}

void Member::setPhone(string newPhone)
{
    phone = newPhone;
}