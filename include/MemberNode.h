
#ifndef MEMBERNODE_H
#define MEMBERNODE_H

#include "Member.h"

class MemberNode
{
public:
    Member member;
    MemberNode* next;

    MemberNode(Member newMember);
};

#endif