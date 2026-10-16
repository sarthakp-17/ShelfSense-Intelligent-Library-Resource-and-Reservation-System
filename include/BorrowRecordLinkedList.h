
#ifndef BORROWRECORDLINKEDLIST_H
#define BORROWRECORDLINKEDLIST_H

#include "BorrowRecordNode.h"
#include <string>
using namespace std;

class BorrowRecordLinkedList
{
private:
    BorrowRecordNode *head;

public:
    BorrowRecordLinkedList();
    ~BorrowRecordLinkedList();

    bool addRecord(BorrowRecord newRecord);

    BorrowRecord *findActiveRecord(string bookId);

    void displayAllRecords() const;

    bool saveToFile(const string &filename) const;
    bool loadFromFile(const string &filename);
    bool returnRecord(string bookId);
    bool renewRecord(string bookId, string newDueDate);
};

#endif