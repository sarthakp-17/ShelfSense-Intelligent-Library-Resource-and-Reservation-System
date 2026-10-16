#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book
{
private:
    string bookId;
    string title;
    string author;
    string category;
    string status;

public:
    Book();

    Book(string id, string bookTitle, string bookAuthor,
         string bookCategory, string bookStatus);

    void displayBook() const;

    string getBookId() const;
    string getTitle() const;
    string getAuthor() const;
    string getCategory() const;
    string getStatus() const;

    void setStatus(string newStatus);
    void setTitle(string newTitle);
    void setAuthor(string newAuthor);
    void setCategory(string newCategory);
};

#endif