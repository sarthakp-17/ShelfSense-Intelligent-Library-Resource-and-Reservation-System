
#include "../include/BorrowRecordLinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

BorrowRecordLinkedList::BorrowRecordLinkedList()
{
    head = nullptr;
}

BorrowRecordLinkedList::~BorrowRecordLinkedList()
{
    while (head != nullptr)
    {
        BorrowRecordNode *temp = head;
        head = head->next;
        delete temp;
    }
}

bool BorrowRecordLinkedList::addRecord(BorrowRecord newRecord)
{
    BorrowRecordNode *newNode =
        new BorrowRecordNode(newRecord);

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        BorrowRecordNode *current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;
    }

    return true;
}

BorrowRecord *BorrowRecordLinkedList::findActiveRecord(
    string bookId)
{
    BorrowRecordNode *current = head;

    while (current != nullptr)
    {
        if (current->record.getBookId() == bookId &&
            current->record.getStatus() == "Issued")
        {
            return &(current->record);
        }

        current = current->next;
    }

    return nullptr;
}

void BorrowRecordLinkedList::displayAllRecords() const
{
    if (head == nullptr)
    {
        cout << "\nNo borrowing records found.\n";
        return;
    }

    BorrowRecordNode *current = head;

    while (current != nullptr)
    {
        current->record.displayRecord();
        cout << "------------------------\n";

        current = current->next;
    }
}

bool BorrowRecordLinkedList::saveToFile(
    const string &filename) const
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Error: Could not save borrowing records.\n";
        return false;
    }

    BorrowRecordNode *current = head;

    while (current != nullptr)
    {
        file << current->record.getMemberId() << "|"
             << current->record.getBookId() << "|"
             << current->record.getIssueDate() << "|"
             << current->record.getDueDate() << "|"
             << current->record.getStatus() << "|"
             << current->record.getFine() << "\n";

        current = current->next;
    }

    return file.good();
}

bool BorrowRecordLinkedList::loadFromFile(
    const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return true;
    }

    string line;

    while (getline(file, line))
    {
        string memberId, bookId, issueDate, dueDate, status;
        double fine = 0.0;

        stringstream ss(line);

        if (getline(ss, memberId, '|') &&
            getline(ss, bookId, '|') &&
            getline(ss, issueDate, '|') &&
            getline(ss, dueDate, '|') &&
            getline(ss, status, '|'))
        {
            // Read the fine if it exists.
            // Old records without a fine default to 0.
            if (!(ss >> fine))
            {
                fine = 0.0;
            }

            BorrowRecord record(
                memberId, bookId, issueDate, dueDate, status);

            record.setFine(fine);
            addRecord(record);
        }
        else
        {
            cout << "Skipping invalid borrowing record.\n";
        }
    }

    return true;
}

bool BorrowRecordLinkedList::returnRecord(string bookId)
{
    BorrowRecord *record = findActiveRecord(bookId);

    if (record == nullptr)
    {
        return false;
    }

    record->setStatus("Returned");
    return true;
}

bool BorrowRecordLinkedList::renewRecord(
    string bookId, string newDueDate)
{
    BorrowRecord *record = findActiveRecord(bookId);

    if (record == nullptr)
    {
        return false;
    }

    record->setDueDate(newDueDate);

    // Reset fine because the due date has changed.
    record->setFine(0.0);

    return true;
}
