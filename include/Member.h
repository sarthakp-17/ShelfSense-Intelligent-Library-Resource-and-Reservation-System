
#ifndef MEMBER_H
#define MEMBER_H

#include <string>
using namespace std;

class Member
{
private:
    string memberId;
    string name;
    string email;
    string phone;

public:
    Member();

    Member(string id, string memberName,
           string memberEmail, string memberPhone);

    void displayMember() const;

    string getMemberId() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;

    void setName(string newName);
    void setEmail(string newEmail);
    void setPhone(string newPhone);
};

#endif