
#include "../include/ReservationQueue.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor
ReservationQueue::ReservationQueue()
{
    front = nullptr;
    rear = nullptr;
}

// Destructor
ReservationQueue::~ReservationQueue()
{
    ReservationNode *current = front;

    while (current != nullptr)
    {
        ReservationNode *temp = current;
        current = current->next;
        delete temp;
    }

    front = nullptr;
    rear = nullptr;
}

// Add reservation to the queue
bool ReservationQueue::enqueue(Reservation reservation)
{
    ReservationNode *newNode = new ReservationNode(reservation);

    if (front == nullptr)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    return true;
}

// Display all reservations
void ReservationQueue::displayReservations() const
{
    if (front == nullptr)
    {
        cout << "No reservations found.\n";
        return;
    }

    ReservationNode *current = front;

    while (current != nullptr)
    {
        current->reservation.displayReservation();
        cout << "----------------------\n";
        current = current->next;
    }
}

// Get the first node
ReservationNode *ReservationQueue::getFront() const
{
    return front;
}

// Save reservations to a file
void ReservationQueue::saveToFile(string filename)
{
    ofstream file(filename);

    if (!file)
    {
        cout << "Error opening reservation file.\n";
        return;
    }

    ReservationNode *current = front;

    while (current != nullptr)
    {
        file << current->reservation.getMemberId() << "|"
             << current->reservation.getBookId() << "|"
             << current->reservation.getReservationDate() << "\n";

        current = current->next;
    }

    file.close();
}

// Load reservations from a file
void ReservationQueue::loadFromFile(string filename)
{
    ifstream file(filename);

    if (!file)
    {
        return;
    }

    string memberId, bookId, date;

    while (getline(file, memberId, '|'))
    {
        if (!getline(file, bookId, '|'))
            break;

        if (!getline(file, date))
            break;

        enqueue(Reservation(memberId, bookId, date));
    }

    file.close();
}

bool ReservationQueue::dequeueNextForBook(string bookId, Reservation &result)
{
    ReservationNode *current = front;
    ReservationNode *previous = nullptr;

    while (current != nullptr)
    {
        if (current->reservation.getBookId() == bookId)
        {
            result = current->reservation;

            // If the matching node is the first node
            if (previous == nullptr)
            {
                front = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            // If the matching node is the last node
            if (current == rear)
            {
                rear = previous;
            }

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}
// Find the next reservation without removing it
bool ReservationQueue::findReservationForBook(
    string bookId,
    Reservation &result) const
{
    ReservationNode *current = front;

    while (current != nullptr)
    {
        if (current->reservation.getBookId() == bookId)
        {
            result = current->reservation;
            return true;
        }

        current = current->next;
    }

    return false;
}

// Remove a reservation only after successful book issuance
bool ReservationQueue::removeNextReservationForBook(
    string bookId)
{
    ReservationNode *current = front;
    ReservationNode *previous = nullptr;

    while (current != nullptr)
    {
        if (current->reservation.getBookId() == bookId)
        {
            if (previous == nullptr)
                front = current->next;
            else
                previous->next = current->next;

            if (current == rear)
                rear = previous;

            delete current;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}