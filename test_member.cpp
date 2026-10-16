
#include "include/MemberLinkedList.h"
#include <iostream>
using namespace std;

int main()
{
    MemberLinkedList members;

    // Add members
    Member m1("M101", "Rahul", "rahul@gmail.com", "9876543210");
    Member m2("M102", "Aman", "aman@gmail.com", "9876543211");

    members.addMember(m1);
    members.addMember(m2);

    // Test duplicate ID
    cout << "\nTesting duplicate ID:\n";
    members.addMember(m1);

    // Display all members
    cout << "\nAll Members:\n";
    members.displayAllMembers();

    // Search for a member
    cout << "\nSearching for M102:\n";
    Member* found = members.searchMember("M102");

    if (found != nullptr)
    {
        found->displayMember();
    }
    else
    {
        cout << "Member not found.\n";
    }

    // Search for a nonexistent member
    cout << "\nSearching for M999:\n";

    if (members.searchMember("M999") == nullptr)
    {
        cout << "Member not found.\n";
    }

    return 0;
}