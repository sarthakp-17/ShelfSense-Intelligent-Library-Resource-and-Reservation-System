
#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include "BookLinkedList.h"
#include "MemberLinkedList.h"
#include "BorrowRecordLinkedList.h"
#include "ReservationQueue.h"
#include "ReservationHistory.h"

void issueBook(
    BookLinkedList &bookList,
    MemberLinkedList &memberList,
    BorrowRecordLinkedList &borrowList);

void returnBook(
    BookLinkedList &bookList,
    BorrowRecordLinkedList &borrowList,
    ReservationQueue &reservationQueue,
    MemberLinkedList &memberList,
    ReservationHistory &reservationHistory);

void renewBook(BorrowRecordLinkedList &borrowList);

void reserveBook(
    BookLinkedList &bookList,
    MemberLinkedList &memberList,
    BorrowRecordLinkedList &borrowList,
    ReservationQueue &reservationQueue,
    ReservationHistory &reservationHistory);

#endif
