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
        if (room->isOccupied())
        {
            return false; // Room is already occupied
        }
        room->occupy();
        reservations.push_back(new Reservation(room, guest, duration));
        return true;
    }
};

bool login()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username != USERNAME || password != PASSWORD)
    {
        throw runtime_error("Invalid username or password.");
    }

    return true;
}

int main()
{
    try
    {
        if (!login())
        {
            return 0;
        }
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    GuestHouse guestHouse;

    while (true)
    {
        cout << "Please select an option:" << endl;
        cout << "1. Reserve a room" << endl;
        cout << "2. View available rooms" << endl;
        cout << "3. View reservations" << endl;
        cout << "4. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter the room number: ";
            int roomNumber;
            cin >> roomNumber;
            if (!guestHouse.isRoomAvailable(roomNumber))
            {
                cout << "Room not available." << endl;
                continue;
            }
            cout << "Enter guest name: ";
            string name;
            cin >> name;
            cout << "Enter guest age: ";
            int age;
            cin >> age;
            cout << "Enter duration in days: ";
            int duration;
            cin >> duration;
            Guest* guest = new Guest(name, age);
            bool success = guestHouse.reserveRoom(roomNumber, guest, duration);
            if (success)
            {
                cout << "Room reserved." << endl;
            }
            else
            {
                cout << "Reservation failed." << endl;
                delete guest;
            }
        }
        else if (choice == 2)
        {
            guestHouse.showRooms();
        }
        else if (choice == 3)
        {
            guestHouse.showReservations();
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}