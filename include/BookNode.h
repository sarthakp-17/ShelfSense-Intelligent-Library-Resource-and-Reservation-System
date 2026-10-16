#ifndef BOOKNODE_H
#define BOOKNODE_H

#include "Book.h"

class BookNode
{
public:
    Book book;
    BookNode* next;

    BookNode(Book newBook);
};

#endif