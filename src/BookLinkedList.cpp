#include "../include/BookLinkedList.h"
#include "../include/ReservationQueue.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

BookLinkedList::BookLinkedList()
{
    head = nullptr;
}

bool BookLinkedList::addBook(Book newBook)
{
    BookNode *current = head;

    // Check whether the Book ID already exists
    while (current != nullptr)
    {
        if (current->book.getBookId() == newBook.getBookId())
        {
            cout << "\nError: Book ID already exists!\n";
            return false;
        }

        current = current->next;
    }

    // ID is unique, so insert the book
    BookNode *newNode = new BookNode(newBook);

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;
    }

    return true;
}
void BookLinkedList::searchBook(string bookId) const
{
    BookNode *current = head;

    while (current != nullptr)
    {
        if (current->book.getBookId() == bookId)
        {
            cout << "\nBook Found!\n";
            current->book.displayBook();
            return;
        }

        current = current->next;
    }

    cout << "\nBook not found!\n";
}

Book *BookLinkedList::findBook(string bookId)
{
    BookNode *current = head;

    while (current != nullptr)
    {
        if (current->book.getBookId() == bookId)
        {
            return &(current->book);
        }

        current = current->next;
    }

    return nullptr;
}

void BookLinkedList::updateBook(string bookId)
{
    BookNode *current = head;

    // Search for the book by ID
    while (current != nullptr)
    {
        if (current->book.getBookId() == bookId)
        {
            string newTitle;
            string newAuthor;
            string newCategory;

            cout << "\n========== UPDATE BOOK ==========\n";

            cout << "Enter new title: ";
            getline(cin >> ws, newTitle);

            cout << "Enter new author: ";
            getline(cin >> ws, newAuthor);

            cout << "Enter new category: ";
            getline(cin >> ws, newCategory);

            // Update the book details
            current->book.setTitle(newTitle);
            current->book.setAuthor(newAuthor);
            current->book.setCategory(newCategory);

            cout << "\nBook updated successfully!\n";

            return;
        }

        current = current->next;
    }

    cout << "\nBook not found! Cannot update.\n";
}

void BookLinkedList::deleteBook(string bookId)
{
    // Case 1: The list is empty
    if (head == nullptr)
    {
        cout << "\nNo books available to delete!\n";
        return;
    }

    // Case 2: The first node contains the book
    if (head->book.getBookId() == bookId)
    {
        BookNode *temp = head;
        head = head->next;

        delete temp;

        cout << "\nBook deleted successfully!\n";
        return;
    }

    // Case 3: Search for the book in the remaining list
    BookNode *current = head;

    while (current->next != nullptr)
    {
        if (current->next->book.getBookId() == bookId)
        {
            BookNode *temp = current->next;

            current->next = temp->next;

            delete temp;

            cout << "\nBook deleted successfully!\n";
            return;
        }

        current = current->next;
    }

    // Case 4: Book ID does not exist
    cout << "\nBook not found! Cannot delete.\n";
}

bool BookLinkedList::saveToFile(const string &filename) const
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "\nError: Could not open file for saving!\n";
        return false;
    }

    BookNode *current = head;

    while (current != nullptr)
    {
        file << current->book.getBookId() << "|"
             << current->book.getTitle() << "|"
             << current->book.getAuthor() << "|"
             << current->book.getCategory() << "|"
             << current->book.getStatus() << "\n";

        current = current->next;
    }

    file.close();
    return true;
}

bool BookLinkedList::loadFromFile(const string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        // The file may not exist on the first run.
        return true;
    }

    string line;

    while (getline(file, line))
    {
        string fields[5];
        stringstream ss(line);
        bool valid = true;

        for (int i = 0; i < 5; i++)
        {
            if (!getline(ss, fields[i], '|'))
            {
                valid = false;
                break;
            }
        }

        // Reject incomplete records or extra fields.
        string extra;
        if (!valid || getline(ss, extra, '|'))
        {
            cout << "\nSkipping invalid book record.\n";
            continue;
        }

        // Prevent duplicate IDs while loading.
        BookNode *current = head;
        bool duplicate = false;

        while (current != nullptr)
        {
            if (current->book.getBookId() == fields[0])
            {
                duplicate = true;
                break;
            }

            current = current->next;
        }

        if (duplicate)
        {
            cout << "\nSkipping duplicate Book ID: "
                 << fields[0] << "\n";
            continue;
        }

        Book newBook(
            fields[0],
            fields[1],
            fields[2],
            fields[3],
            fields[4]);

        addBook(newBook);
    }

    file.close();
    return true;
}

void BookLinkedList::displayBooks(
    const ReservationQueue &reservationQueue) const
{
    BookNode *current = head;

    while (current != nullptr)
    {
        current->book.displayBook();

        if (current->book.getStatus() == "Reserved")
        {
            Reservation reservation;

            if (reservationQueue.findReservationForBook(
                    current->book.getBookId(), reservation))
            {
                cout << "Reserved for Member ID: "
                     << reservation.getMemberId() << '\n';
            }
        }

        current = current->next;
    }
}