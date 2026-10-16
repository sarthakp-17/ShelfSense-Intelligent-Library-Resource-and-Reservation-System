#include "../include/Book.h"
#include <iostream>

using namespace std;

Book::Book()
{
    bookId = "";
    title = "";
    author = "";
    category = "";
    status = "Available";
}

Book::Book(string id, string bookTitle, string bookAuthor,
           string bookCategory, string bookStatus)
{
    bookId = id;
    title = bookTitle;
    author = bookAuthor;
    category = bookCategory;
    status = bookStatus;
}

void Book::displayBook() const
{
    cout << "\nBook ID  : " << bookId;
    cout << "\nTitle    : " << title;
    cout << "\nAuthor   : " << author;
    cout << "\nCategory : " << category;
    cout << "\nStatus   : " << status << "\n";
}

string Book::getBookId() const
{
    return bookId;
}

string Book::getTitle() const
{
    return title;
}

string Book::getAuthor() const
{
    return author;
}

string Book::getCategory() const
{
    return category;
}

string Book::getStatus() const
{
    return status;
}

void Book::setStatus(string newStatus)
{
    status = newStatus;
}
void Book::setTitle(string newTitle)
{
    title = newTitle;
}

void Book::setAuthor(string newAuthor)
{
    author = newAuthor;
}

void Book::setCategory(string newCategory)
{
    category = newCategory;
}