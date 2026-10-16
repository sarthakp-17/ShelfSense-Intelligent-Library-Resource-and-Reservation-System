#include "../include/Reservation.h"
#include <iostream>

using namespace std;

// Default constructor
Reservation::Reservation()
{
    memberId = "";
    bookId = "";
    reservationDate = "";
    status = "Pending";
}

// Parameterized constructor
Reservation::Reservation(string mId, string bId, string date)
{
    memberId = mId;
    bookId = bId;
    reservationDate = date;
    status = "Pending";
}

// Parameterized constructor with status
Reservation::Reservation(
    string mId, string bId, string date, string reservationStatus)
{
    memberId = mId;
    bookId = bId;
    reservationDate = date;
    status = reservationStatus;
}

// Getter functions
string Reservation::getMemberId() const
{
    return memberId;
}

string Reservation::getBookId() const
{
    return bookId;
}

string Reservation::getReservationDate() const
{
    return reservationDate;
}

string Reservation::getStatus() const
{
    return status;
}

// Update reservation status
void Reservation::setStatus(string newStatus)
{
    status = newStatus;
}

// Display reservation details
void Reservation::displayReservation() const
{
    cout << "Member ID: " << memberId << endl;
    cout << "Book ID: " << bookId << endl;
    cout << "Reservation Date: " << reservationDate << endl;
    cout << "Status: " << status << endl;
}