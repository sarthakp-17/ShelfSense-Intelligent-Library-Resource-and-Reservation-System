
#include <iostream>
#include <string>
#include <limits>

#include "../include/Book.h"
#include "../include/BookNode.h"
#include "../include/BookLinkedList.h"
#include "../include/Member.h"
#include "../include/MemberLinkedList.h"
#include "../include/BorrowRecordLinkedList.h"
#include "../include/LibraryManager.h"
#include "../include/ReservationQueue.h"
#include "../include/ReservationHistory.h"

// ================= BOOK MENU =================

void displayBookMenu()
{
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "             BOOK MANAGEMENT                \n";
    std::cout << "============================================\n";

    std::cout << "1. Add Book\n";
    std::cout << "2. Display Books\n";
    std::cout << "3. Search Book\n";
    std::cout << "4. Update Book\n";
    std::cout << "5. Delete Book\n";
    std::cout << "6. Back\n";

    std::cout << "--------------------------------------------\n";
    std::cout << "Enter your choice: ";
}

// ================= MEMBER MENU =================

void displayMemberMenu()
{
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "            MEMBER MANAGEMENT               \n";
    std::cout << "============================================\n";

    std::cout << "1. Add Member\n";
    std::cout << "2. Display All Members\n";
    std::cout << "3. Search Member\n";
    std::cout << "4. Back\n";

    std::cout << "--------------------------------------------\n";
    std::cout << "Enter your choice: ";
}

// ================= MAIN MENU =================

void displayMainMenu()
{
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "              S H E L F S E N S E           \n";
    std::cout << "          Intelligent Library System        \n";
    std::cout << "============================================\n";

    std::cout << "\n--------------- MAIN MENU ------------------\n";

    std::cout << "1. Book Management\n";
    std::cout << "2. Member Management\n";
    std::cout << "3. Issue Book\n";
    std::cout << "4. Return Book\n";
    std::cout << "5. Renew Book\n";
    std::cout << "6. Reserve Book\n";
    std::cout << "7. Search and Sort\n";
    std::cout << "8. Due / Overdue Dashboard\n";
    std::cout << "9. Transaction History\n";
    std::cout << "10. View Borrowing Records\n";
    std::cout << "11. Reservation History\n";
    std::cout << "0. Exit\n";

    std::cout << "--------------------------------------------\n";
    std::cout << "Enter your choice: ";
}

// ================= MAIN =================

int main()
{
    int choice = -1;

    std::cout << "============================================\n";
    std::cout << "              WELCOME TO                    \n";
    std::cout << "              S H E L F S E N S E           \n";
    std::cout << "============================================\n";

    // Create Book Linked List
    BookLinkedList bookList;

    // Load saved books
    if (bookList.loadFromFile("books.txt"))
    {
        std::cout << "\nBook data loaded successfully.\n";
    }

    // Create Member Linked List
    MemberLinkedList memberList;

    // Load saved members
    if (memberList.loadFromFile("members.txt"))
    {
        std::cout << "\nMember data loaded successfully.\n";
    }

    // Create Borrow Record Linked List
    BorrowRecordLinkedList borrowList;

    // Load saved borrowing records
    if (borrowList.loadFromFile("borrow_records.txt"))
    {
        std::cout << "\nBorrowing records loaded successfully.\n";
    }

    // Create Reservation Queue
    ReservationQueue reservationQueue;
    reservationQueue.loadFromFile("reservations.txt");

    // Create and load Reservation History
    ReservationHistory reservationHistory;
    reservationHistory.loadFromFile("reservation_history.txt");

    do
    {
        displayMainMenu();

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "\nPlease enter a valid number.\n";
            continue;
        }

        switch (choice)
        {
            // ================= BOOK MANAGEMENT =================

        case 1:
        {
            int bookChoice = 0;

            do
            {
                displayBookMenu();

                if (!(std::cin >> bookChoice))
                {
                    std::cin.clear();
                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(), '\n');
                    bookChoice = 0;
                    std::cout << "\nInvalid input.\n";
                    continue;
                }

                switch (bookChoice)
                {
                case 1:
                {
                    std::string id, title, author, category;

                    std::cout << "\n========== ADD BOOK ==========\n";
                    std::cout << "Enter Book ID: ";
                    std::cin >> id;

                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "Enter Title: ";
                    std::getline(std::cin, title);

                    std::cout << "Enter Author: ";
                    std::getline(std::cin, author);

                    std::cout << "Enter Category: ";
                    std::getline(std::cin, category);

                    Book newBook(id, title, author, category, "Available");

                    if (bookList.addBook(newBook))
                    {
                        std::cout << "\nBook added successfully!\n";

                        if (!bookList.saveToFile("books.txt"))
                        {
                            std::cout << "Warning: Book data could not be saved!\n";
                        }
                    }

                    break;
                }

                case 2:
                    std::cout << "\n========== BOOK LIST ==========\n";
                    bookList.displayBooks(reservationQueue);
                    break;

                case 3:
                {
                    std::string searchId;

                    std::cout << "\n========== SEARCH BOOK ==========\n";
                    std::cout << "Enter Book ID to search: ";
                    std::cin >> searchId;

                    bookList.searchBook(searchId);
                    break;
                }

                case 4:
                {
                    std::string updateId;

                    std::cout << "\n========== UPDATE BOOK ==========\n";
                    std::cout << "Enter Book ID to update: ";
                    std::cin >> updateId;

                    bookList.updateBook(updateId);

                    if (!bookList.saveToFile("books.txt"))
                    {
                        std::cout << "Warning: Could not save updated books!\n";
                    }

                    break;
                }

                case 5:
                {
                    std::string deleteId;

                    std::cout << "\n========== DELETE BOOK ==========\n";
                    std::cout << "Enter Book ID to delete: ";
                    std::cin >> deleteId;

                    bookList.deleteBook(deleteId);

                    if (!bookList.saveToFile("books.txt"))
                    {
                        std::cout << "Warning: Could not save deleted books!\n";
                    }

                    break;
                }

                case 6:
                    std::cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    std::cout << "\nInvalid choice! Please try again.\n";
                }

            } while (bookChoice != 6);

            break;
        }

            // ================= MEMBER MANAGEMENT =================

        case 2:
        {
            int memberChoice = 0;

            do
            {
                displayMemberMenu();

                if (!(std::cin >> memberChoice))
                {
                    std::cin.clear();
                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(), '\n');
                    memberChoice = 0;
                    std::cout << "\nInvalid input.\n";
                    continue;
                }

                switch (memberChoice)
                {
                case 1:
                {
                    std::string id, name, email, phone;

                    std::cout << "\n========== ADD MEMBER ==========\n";
                    std::cout << "Enter Member ID: ";
                    std::cin >> id;

                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "Enter Name: ";
                    std::getline(std::cin, name);

                    std::cout << "Enter Email: ";
                    std::getline(std::cin, email);

                    std::cout << "Enter Phone: ";
                    std::getline(std::cin, phone);

                    Member newMember(id, name, email, phone);

                    if (memberList.addMember(newMember))
                    {
                        if (memberList.saveToFile("members.txt"))
                        {
                            std::cout << "Member data saved successfully.\n";
                        }
                        else
                        {
                            std::cout << "Warning: Member data could not be saved!\n";
                        }
                    }

                    break;
                }

                case 2:
                    std::cout << "\n========== MEMBER LIST ==========\n";
                    memberList.displayAllMembers();
                    break;

                case 3:
                {
                    std::string searchId;

                    std::cout << "\n========== SEARCH MEMBER ==========\n";
                    std::cout << "Enter Member ID: ";
                    std::cin >> searchId;

                    Member *found = memberList.searchMember(searchId);

                    if (found != nullptr)
                    {
                        std::cout << "\nMember found:\n";
                        found->displayMember();
                    }
                    else
                    {
                        std::cout << "\nMember not found.\n";
                    }

                    break;
                }

                case 4:
                    std::cout << "\nReturning to Main Menu...\n";
                    break;

                default:
                    std::cout << "\nInvalid choice! Please try again.\n";
                }

            } while (memberChoice != 4);

            break;
        }

            // ================= ISSUE BOOK =================

        case 3:
            issueBook(bookList, memberList, borrowList);
            bookList.saveToFile("books.txt");
            borrowList.saveToFile("borrow_records.txt");
            break;

            // ================= RETURN BOOK =================

            // ================= RETURN BOOK =================

        case 4:
            returnBook(
                bookList,
                borrowList,
                reservationQueue,
                memberList,
                reservationHistory);

            bookList.saveToFile("books.txt");
            borrowList.saveToFile("borrow_records.txt");
            reservationQueue.saveToFile("reservations.txt");
            reservationHistory.saveToFile("reservation_history.txt");
            break;

            // ================= RENEW BOOK =================

        case 5:
            renewBook(borrowList);
            borrowList.saveToFile("borrow_records.txt");
            break;

            // ================= RESERVE BOOK =================

            // ================= RESERVE BOOK =================

        case 6:
            reserveBook(
                bookList,
                memberList,
                borrowList,
                reservationQueue,
                reservationHistory);

            reservationQueue.saveToFile("reservations.txt");
            reservationHistory.saveToFile("reservation_history.txt");
            break;

            // ================= SEARCH AND SORT =================

        case 7:
            std::cout << "\nSearch and Sort selected.\n";
            break;

            // ================= DASHBOARD =================

        case 8:
            std::cout << "\nDue / Overdue Dashboard selected.\n";
            break;

            // ================= TRANSACTION HISTORY =================

        case 9:
            std::cout << "\nTransaction History selected.\n";
            break;

            // ================= BORROWING RECORDS =================

        case 10:
            std::cout << "\n========== BORROWING RECORDS ==========\n";
            borrowList.displayAllRecords();
            break;
            // ================= RESERVATION HISTORY =================

        case 11:
            reservationHistory.displayHistory();
            break;

            // ================= EXIT =================

            // ================= EXIT =================

        case 0:
            reservationQueue.saveToFile("reservations.txt");
            reservationHistory.saveToFile("reservation_history.txt");

            std::cout << "\nThank you for using ShelfSense!\n";
            break;

        default:
            std::cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
