#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation
{
private:
    string memberId;
    string bookId;
    string reservationDate;
    string status;

public:
    Reservation();

    Reservation(string mId, string bId, string date);
    Reservation(string mId, string bId, string date, string reservationStatus);

    string getMemberId() const;
    string getBookId() const;
    string getReservationDate() const;
    string getStatus() const;

    void setStatus(string newStatus);

    void displayReservation() const;
};

#endif