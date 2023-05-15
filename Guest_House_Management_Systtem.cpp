#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

const string USERNAME = "admin";
const string PASSWORD = "password";

class Room
{
private:
    int number;
    int capacity;
    bool occupied;

public:
    Room(int number, int capacity)
    {
        this->number = number;
        this->capacity = capacity;
        this->occupied = false;
    }

    int getNumber() const
    {
        return number;
    }

    int getCapacity() const
    {
        return capacity;
    }

    bool isOccupied() const
    {
        return occupied;
    }

    void occupy()
    {
        occupied = true;
    }

    void vacate()
    {
        occupied = false;
    }

    friend ostream &operator<<(ostream &os, const Room &room)
    {
        os << "Room " << room.getNumber() << " (Capacity: " << room.getCapacity() << ", Occupied: " << (room.isOccupied() ? "Yes" : "No") << ")";
        return os;
    }
};

class Guest
{
private:
    string name;
    int age;

public:
    Guest(const string& name, int age)
    {
        this->name = name;
        this->age = age;
    }

    const string& getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    friend ostream &operator<<(ostream &os, const Guest &guest)
    {
        os << guest.getName() << " (" << guest.getAge() << " years old)";
        return os;
    }
};

class Reservation
{
private:
    Room* room;
    Guest* guest;
    int duration;

public:
    Reservation(Room* room, Guest* guest, int duration)
    {
        this->room = room;
        this->guest = guest;
        this->duration = duration;
        }

    Room* getRoom() const
    {
        return room;
    }

    Guest* getGuest() const
    {
        return guest;
    }

    int getDuration() const
    {
        return duration;
    }

    friend ostream &operator<<(ostream &os, const Reservation &reservation)
    {
        os << *reservation.getGuest() << " reserved " << *reservation.getRoom() << " for " << reservation.getDuration() << " days";
        return os;
    }
};

class GuestHouse
{
private:
    vector<Room*> rooms;
    vector<Reservation*> reservations;

public:
    GuestHouse()
    {
        for (int i = 1; i <= 10; i++)
        {
            rooms.push_back(new Room(i, 2));
        }
    }

    ~GuestHouse()
    {
        for (auto room : rooms)
        {
            delete room;
        }
        for (auto reservation : reservations)
        {
            delete reservation;
        }
    }

    void showRooms() const
    {
        cout << "Rooms:" << endl;
        for (auto room : rooms)
        {
            cout << *room << endl;
        }
    }

    void showReservations() const
    {
        cout << "Reservations:" << endl;
        for (auto reservation : reservations)
        {
            cout << *reservation << endl;
        }
    }

    bool isRoomAvailable(int number) const
    {
        for (auto room : rooms)
        {
            if (room->getNumber() == number)
            {
                return !room->isOccupied();
            }
        }
        return false;
    }

    Room* getRoom(int number) const
    {
        for (auto room : rooms)
        {
            if (room->getNumber() == number)
            {
                return room;
            }
        }
        return nullptr;
    }

    bool reserveRoom(int roomNumber, Guest* guest, int duration)
    {
        Room* room = getRoom(roomNumber);
        if (room == nullptr)
        {
            return false; // Room with given number doesn't exist
        }