
#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include <string>
using namespace std;

class BorrowRecord
{
private:
    string memberId;
    string bookId;
    string issueDate;
    string dueDate;
    string status;
    double fine;

public:
    BorrowRecord();

    BorrowRecord(string mId, string bId,
                 string issued, string due,
                 string recordStatus);

    string getMemberId() const;
    string getBookId() const;
    string getIssueDate() const;
    string getDueDate() const;
    string getStatus() const;

    void setStatus(string newStatus);
    double getFine();
    void setFine(double amount);
    void setDueDate(string newDueDate);
    void displayRecord() const;
};

#endif