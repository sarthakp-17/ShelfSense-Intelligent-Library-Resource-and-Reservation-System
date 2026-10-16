#ifndef RESERVATIONHISTORY_H
#define RESERVATIONHISTORY_H

#include <string>
#include <vector>
#include "Reservation.h"

using namespace std;

class ReservationHistory
{
private:
    vector<Reservation> history;

public:
    void addReservation(Reservation reservation);

    bool markFulfilled(
        string memberId,
        string bookId,
        string reservationDate);

    void displayHistory() const;

    bool saveToFile(string filename) const;
    bool loadFromFile(string filename);
};

#endif