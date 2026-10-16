
#include "../include/MemberLinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Constructor
MemberLinkedList::MemberLinkedList()
{
    head = nullptr;
}

// Destructor
MemberLinkedList::~MemberLinkedList()
{
    MemberNode *current = head;

    while (current != nullptr)
    {
        MemberNode *temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
}

// Check whether the list is empty
bool MemberLinkedList::isEmpty() const
{
    return head == nullptr;
}

// Search for a member using member ID
Member *MemberLinkedList::searchMember(string id)
{
    MemberNode *current = head;

    while (current != nullptr)
    {
        if (current->member.getMemberId() == id)
        {
            return &(current->member);
        }

        current = current->next;
    }

    return nullptr;
}

// Add a new member
bool MemberLinkedList::addMember(Member newMember)
{
    // Prevent duplicate member IDs
    if (searchMember(newMember.getMemberId()) != nullptr)
    {
        cout << "Error: Member ID already exists!" << endl;
        return false;
    }

    // Create a new node
    MemberNode *newNode = new MemberNode(newMember);

    // Insert at the beginning of the list
    newNode->next = head;
    head = newNode;

    cout << "Member added successfully!" << endl;
    return true;
}

// Display all members
void MemberLinkedList::displayAllMembers() const
{
    if (head == nullptr)
    {
        cout << "No members found." << endl;
        return;
    }

    MemberNode *current = head;

    while (current != nullptr)
    {
        current->member.displayMember();
        cout << "------------------------" << endl;

        current = current->next;
    }
}

// Save all members to a file
bool MemberLinkedList::saveToFile(const string &filename) const
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Error opening file for saving members.\n";
        return false;
    }

    MemberNode *current = head;

    while (current != nullptr)
    {
        file << current->member.getMemberId() << "|"
             << current->member.getName() << "|"
             << current->member.getEmail() << "|"
             << current->member.getPhone() << "\n";

        current = current->next;
    }

    file.close();
    return true;
}

// Load members from a file
bool MemberLinkedList::loadFromFile(const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    // Clear existing nodes before loading
    while (head != nullptr)
    {
        MemberNode *temp = head;
        head = head->next;
        delete temp;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id, name, email, phone;

        if (getline(ss, id, '|') &&
            getline(ss, name, '|') &&
            getline(ss, email, '|') &&
            getline(ss, phone))
        {
            // Ignore records with an empty ID
            if (id.empty())
            {
                continue;
            }

            // Avoid duplicate IDs in the file
            if (searchMember(id) == nullptr)
            {
                Member newMember(id, name, email, phone);

                MemberNode *newNode = new MemberNode(newMember);
                newNode->next = head;
                head = newNode;
            }
        }
    }

    file.close();
    return true;
}