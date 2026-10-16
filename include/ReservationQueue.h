
#ifndef RESERVATIONQUEUE_H
#define RESERVATIONQUEUE_H

#include "ReservationNode.h"
#include <string>

using namespace std;

class ReservationQueue
{
private:
    ReservationNode *front;
    ReservationNode *rear;

public:
    ReservationQueue();
    ~ReservationQueue();

    bool enqueue(Reservation reservation);
    void displayReservations() const;

    ReservationNode *getFront() const;

    void saveToFile(string filename);
    void loadFromFile(string filename);

    bool dequeueNextForBook(string bookId, Reservation &result);
    bool findReservationForBook(
        string bookId,
        Reservation &result) const;

    bool removeNextReservationForBook(
        string bookId);
};

#endif
