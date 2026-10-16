
#ifndef BORROWRECORDNODE_H
#define BORROWRECORDNODE_H

#include "BorrowRecord.h"

class BorrowRecordNode
{
public:
    BorrowRecord record;
    BorrowRecordNode* next;

    BorrowRecordNode(BorrowRecord newRecord);
};

#endif