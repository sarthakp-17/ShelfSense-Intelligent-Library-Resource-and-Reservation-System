
#ifndef RESERVATIONNODE_H
#define RESERVATIONNODE_H

#include "Reservation.h"

class ReservationNode
{
public:
    Reservation reservation;
    ReservationNode* next;

    ReservationNode(Reservation r);
};

#endif
