#include "../include/ReservationHistory.h"
#include <iostream>
#include <fstream>

using namespace std;

// Add a reservation to history
void ReservationHistory::addReservation(Reservation reservation)
{
    history.push_back(reservation);
}

// Mark a reservation as fulfilled
bool ReservationHistory::markFulfilled(
    string memberId,
    string bookId,
    string reservationDate)
{
    for (int i = static_cast<int>(history.size()) - 1; i >= 0; i--)
    {
        if (history[i].getMemberId() == memberId &&
            history[i].getBookId() == bookId &&
            history[i].getReservationDate() == reservationDate &&
            history[i].getStatus() == "Pending")
        {
            history[i].setStatus("Fulfilled");
            return true;
        }
    }

    return false;
}

// Display reservation history
void ReservationHistory::displayHistory() const
{
    if (history.empty())
    {
        cout << "\nNo reservation history found.\n";
        return;
    }

    cout << "\n========== RESERVATION HISTORY ==========\n";

    for (const Reservation &reservation : history)
    {
        reservation.displayReservation();
        cout << "-----------------------------------------\n";
    }
}

// Save history to file
bool ReservationHistory::saveToFile(string filename) const
{
    ofstream file(filename);

    if (!file)
    {
        cout << "Error opening reservation history file.\n";
        return false;
    }

    for (const Reservation &reservation : history)
    {
        file << reservation.getMemberId() << "|"
             << reservation.getBookId() << "|"
             << reservation.getReservationDate() << "|"
             << reservation.getStatus() << "\n";
    }

    file.close();
    return true;
}

// Load history from file
bool ReservationHistory::loadFromFile(string filename)
{
    ifstream file(filename);

    if (!file)
    {
        return false;
    }

    history.clear();

    string memberId, bookId, date, status;

    while (getline(file, memberId, '|'))
    {
        if (!getline(file, bookId, '|'))
            break;

        if (!getline(file, date, '|'))
            break;

        if (!getline(file, status))
            break;

        history.push_back(
            Reservation(memberId, bookId, date, status));
    }

    file.close();
    return true;
}