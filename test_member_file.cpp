
#include "include/MemberLinkedList.h"
#include <iostream>
using namespace std;

int main()
{
    MemberLinkedList members;

    members.addMember(
        Member("M101", "Rahul", "rahul@gmail.com", "9876543210")
    );

    members.addMember(
        Member("M102", "Aman", "aman@gmail.com", "9876543211")
    );

    if (members.saveToFile("members.txt"))
        cout << "Members saved successfully.\n";

    MemberLinkedList loadedMembers;

    if (loadedMembers.loadFromFile("members.txt"))
        cout << "Members loaded successfully.\n";

    loadedMembers.displayAllMembers();

    return 0;
}