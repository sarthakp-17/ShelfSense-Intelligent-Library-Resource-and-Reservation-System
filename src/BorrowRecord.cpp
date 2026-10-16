
#include "../include/BorrowRecord.h"
#include <iostream>

using namespace std;

BorrowRecord::BorrowRecord()
{
    memberId = "";
    bookId = "";
    issueDate = "";
    dueDate = "";
    status = "Issued";
    fine = 0;
}

BorrowRecord::BorrowRecord(string mId, string bId,
                           string issued, string due,
                           string recordStatus)
{
    memberId = mId;
    bookId = bId;
    issueDate = issued;
    dueDate = due;
    status = recordStatus;
}

string BorrowRecord::getMemberId() const
{
    return memberId;
}

string BorrowRecord::getBookId() const
{
    return bookId;
}

string BorrowRecord::getIssueDate() const
{
    return issueDate;
}

string BorrowRecord::getDueDate() const
{
    return dueDate;
}

string BorrowRecord::getStatus() const
{
    return status;
}

void BorrowRecord::setStatus(string newStatus)
{
    status = newStatus;
}
double BorrowRecord::getFine()
{
    return fine;
}

void BorrowRecord::setFine(double amount)
{
    fine = amount;
}
void BorrowRecord::setDueDate(string newDueDate)
{
    dueDate = newDueDate;
}

void BorrowRecord::displayRecord() const
{
    cout << "Member ID: " << memberId << endl;
    cout << "Book ID: " << bookId << endl;
    cout << "Issue Date: " << issueDate << endl;
    cout << "Due Date: " << dueDate << endl;
    cout << "Status: " << status << endl;
    cout << "Fine: Rs. " << fine << '\n';
}