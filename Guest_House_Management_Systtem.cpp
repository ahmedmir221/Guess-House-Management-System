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