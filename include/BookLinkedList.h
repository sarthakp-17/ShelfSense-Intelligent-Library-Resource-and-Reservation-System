#ifndef BOOKLINKEDLIST_H
#define BOOKLINKEDLIST_H

#include "BookNode.h"
#include "ReservationQueue.h"

class BookLinkedList
{
private:
    BookNode *head;

public:
    BookLinkedList();

    bool addBook(Book newBook);
    void displayBooks(const ReservationQueue &reservationQueue) const;
    void searchBook(string bookId) const;
    void updateBook(string bookId);
    void deleteBook(string bookId);
    bool saveToFile(const string &filename) const;
    bool loadFromFile(const string &filename);
    Book *findBook(string bookId);
};

#endif