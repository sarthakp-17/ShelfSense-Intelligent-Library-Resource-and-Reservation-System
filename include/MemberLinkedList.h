
#ifndef MEMBERLINKEDLIST_H
#define MEMBERLINKEDLIST_H

#include "MemberNode.h"

class MemberLinkedList
{
private:
    MemberNode *head;

public:
    MemberLinkedList();

    ~MemberLinkedList();

    bool addMember(Member newMember);

    Member *searchMember(string id);

    void displayAllMembers() const;

    bool isEmpty() const;
    bool saveToFile(const string &filename) const;
    bool loadFromFile(const string &filename);
};

#endif