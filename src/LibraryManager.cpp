#include "../include/ReservationHistory.h"
#include "../include/LibraryManager.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

int calculateLateDays(string dueDate, string returnDate)
{
    int dueDay, dueMonth, dueYear;
    int returnDay, returnMonth, returnYear;

    sscanf(dueDate.c_str(), "%d-%d-%d",
           &dueDay, &dueMonth, &dueYear);

    sscanf(returnDate.c_str(), "%d-%d-%d",
           &returnDay, &returnMonth, &returnYear);

    tm due = {};
    due.tm_mday = dueDay;
    due.tm_mon = dueMonth - 1;
    due.tm_year = dueYear - 1900;

    tm returned = {};
    returned.tm_mday = returnDay;
    returned.tm_mon = returnMonth - 1;
    returned.tm_year = returnYear - 1900;

    time_t dueTime = mktime(&due);
    time_t returnTime = mktime(&returned);

    double difference = difftime(returnTime, dueTime);
    int lateDays = static_cast<int>(difference / 86400);

    return (lateDays > 0) ? lateDays : 0;
}
void issueBook(
    BookLinkedList &bookList,
    MemberLinkedList &memberList,
    BorrowRecordLinkedList &borrowList)
{
    string memberId, bookId, issueDate, dueDate;

    cout << "\n===== ISSUE BOOK =====\n";

    cout << "Enter Member ID: ";
    cin >> memberId;

    Member *member = memberList.searchMember(memberId);

    if (member == nullptr)
    {
        cout << "Error: Member not found.\n";
        return;
    }

    cout << "Enter Book ID: ";
    cin >> bookId;

    Book *book = bookList.findBook(bookId);

    if (book == nullptr)
    {
        cout << "Error: Book not found.\n";
        return;
    }

    if (book->getStatus() != "Available")
    {
        cout << "Error: Book is not available.\n";
        return;
    }

    cout << "Enter issue date (DD-MM-YYYY): ";
    cin >> issueDate;

    cout << "Enter due date (DD-MM-YYYY): ";
    cin >> dueDate;

    BorrowRecord record(
        memberId,
        bookId,
        issueDate,
        dueDate,
        "Issued");

    if (borrowList.addRecord(record))
    {
        book->setStatus("Issued");

        cout << "\nBook issued successfully!\n";
        cout << "Member: " << memberId << '\n';
        cout << "Book: " << book->getTitle() << '\n';
        cout << "Due date: " << dueDate << '\n';
    }
    else
    {
        cout << "Error: Could not create borrowing record.\n";
    }
}

void returnBook(
    BookLinkedList &bookList,
    BorrowRecordLinkedList &borrowList,
    ReservationQueue &reservationQueue,
    MemberLinkedList &memberList,
    ReservationHistory &reservationHistory)
{
    string bookId, returnDate;

    cout << "\n===== RETURN BOOK =====\n";
    cout << "Enter Book ID: ";
    cin >> bookId;

    Book *book = bookList.findBook(bookId);

    if (book == nullptr)
    {
        cout << "Error: Book not found.\n";
        return;
    }

    if (book->getStatus() != "Issued")
    {
        cout << "Error: This book is not currently issued.\n";
        return;
    }

    BorrowRecord *record =
        borrowList.findActiveRecord(bookId);

    if (record == nullptr)
    {
        cout << "Error: Active borrowing record not found.\n";
        return;
    }

    cout << "Due Date: " << record->getDueDate() << '\n';
    cout << "Enter Return Date (DD-MM-YYYY): ";
    cin >> returnDate;

    int lateDays =
        calculateLateDays(record->getDueDate(), returnDate);

    double fine = lateDays * 5.0;
    record->setFine(fine);

    if (!borrowList.returnRecord(bookId))
    {
        cout << "Error: Could not return the book.\n";
        return;
    }

    cout << "\nBook returned successfully!\n";
    cout << "Book: " << book->getTitle() << '\n';
    cout << "Late Days: " << lateDays << '\n';
    cout << "Fine: Rs. " << fine << '\n';

    Reservation nextReservation;

    if (reservationQueue.findReservationForBook(
            bookId, nextReservation))
    {
        string nextMemberId = nextReservation.getMemberId();

        Member *member =
            memberList.searchMember(nextMemberId);

        if (member == nullptr)
        {
            book->setStatus("Reserved");
            cout << "Reserved member not found.\n";
            cout << "Book remains Reserved.\n";
            return;
        }

        string dueDate;

        cout << "\n===== AUTOMATIC BOOK ISSUANCE =====\n";
        cout << "Reserved Member: " << nextMemberId << '\n';
        cout << "Book: " << book->getTitle() << '\n';
        cout << "Enter new due date (DD-MM-YYYY): ";
        cin >> dueDate;

        BorrowRecord newRecord(
            nextMemberId,
            bookId,
            returnDate,
            dueDate,
            "Issued");

        if (borrowList.addRecord(newRecord))
        {
            // Mark the reservation as fulfilled in history
            reservationHistory.markFulfilled(
                nextReservation.getMemberId(),
                nextReservation.getBookId(),
                nextReservation.getReservationDate());
            reservationQueue.removeNextReservationForBook(bookId);

            book->setStatus("Issued");

            cout << "\nBook issued automatically!\n";
            cout << "Member ID: " << nextMemberId << '\n';
            cout << "Book ID: " << bookId << '\n';
            cout << "Issue Date: " << returnDate << '\n';
            cout << "Due Date: " << dueDate << '\n';
            cout << "Status: Issued\n";
        }
        else
        {
            book->setStatus("Reserved");
            cout << "Could not create borrowing record.\n";
            cout << "Book remains Reserved.\n";
        }
    }
    else
    {
        book->setStatus("Available");
        cout << "Status: Available\n";
    }
}

void renewBook(BorrowRecordLinkedList &borrowList)
{
    string bookId, newDueDate;

    cout << "\n===== RENEW BOOK =====\n";
    cout << "Enter Book ID: ";
    cin >> bookId;

    BorrowRecord *record = borrowList.findActiveRecord(bookId);

    if (record == nullptr)
    {
        cout << "Error: No active borrowing record found.\n";
        return;
    }

    cout << "Current Due Date: "
         << record->getDueDate() << '\n';

    cout << "Enter New Due Date (DD-MM-YYYY): ";
    cin >> newDueDate;

    if (borrowList.renewRecord(bookId, newDueDate))
    {
        cout << "\nBook renewed successfully!\n";
        cout << "New Due Date: " << newDueDate << '\n';
    }
    else
    {
        cout << "Error: Could not renew the book.\n";
    }
}
void reserveBook(
    BookLinkedList &bookList,
    MemberLinkedList &memberList,
    BorrowRecordLinkedList &borrowList,
    ReservationQueue &reservationQueue,
    ReservationHistory &reservationHistory)
{
    string memberId, bookId, reservationDate;

    cout << "\n===== RESERVE BOOK =====\n";

    cout << "Enter Member ID: ";
    cin >> memberId;

    Member *member = memberList.searchMember(memberId);

    if (member == nullptr)
    {
        cout << "Error: Member not found.\n";
        return;
    }

    cout << "Enter Book ID: ";
    cin >> bookId;

    Book *book = bookList.findBook(bookId);

    if (book == nullptr)
    {
        cout << "Error: Book not found.\n";
        return;
    }

    if (book->getStatus() == "Available")
    {
        cout << "This book is available. You can issue it directly.\n";
        return;
    }

    BorrowRecord *activeRecord =
        borrowList.findActiveRecord(bookId);

    if (activeRecord == nullptr)
    {
        cout << "Error: Active borrowing record not found.\n";
        return;
    }

    cout << "Enter Reservation Date (DD-MM-YYYY): ";
    cin >> reservationDate;

    Reservation reservation(
        memberId,
        bookId,
        reservationDate);

    if (reservationQueue.enqueue(reservation))
    {
        // Add the reservation to history as Pending
        reservationHistory.addReservation(reservation);
        cout << "\nReservation added successfully!\n";
        cout << "Member ID: " << memberId << '\n';
        cout << "Book: " << book->getTitle() << '\n';
        cout << "Reservation Date: "
             << reservationDate << '\n';
    }
    else
    {
        cout << "Error: Could not add reservation.\n";
    }
}