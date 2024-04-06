#ifndef STOP_CPP
#define STOP_CPP

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//Stop is the node struct for each node in the Route linked list
//You can think of a stop as a train stop on the light rail in Baltimore
struct Stop {
public:
    // Name: Stop - Default constructor
    // Desc - Default constructor for a Stop node
    // Preconditions - None
    // Postconditions - Creates a new Stop (for the Route)
    Stop() : m_next(nullptr) {}

    // Name: Stop (Name, number) - Overloaded Constructor
    // Desc - Overloaded constructor
    // Preconditions - Must have name and number to create new stop
    // Postconditions - Creates a new Stop (for the Route)
    Stop(string name, int number) {
        m_name = name;
        m_number = number;
        m_next = nullptr;
    }

    // Name: GetName()
    // Desc - Returns the name of the stop
    // Preconditions - None
    // Postconditions - Returns a read-only m_name
    string GetName() {
        return m_name;
    }

    // Name: GetNumber()
    // Desc - Returns the number of the stop
    // Preconditions - None
    // Postconditions - Returns a read-only m_number
    int GetNumber() {
        return m_number;
    }

    // Name: GetNextStop()
    // Desc - Returns a pointer to the next stop
    // Preconditions - None
    // Postconditions - Returns the pointer to the next stop
    Stop* GetNextStop() {
        return m_next;
    }

    // Name: SetNextStop()
    // Desc - Sets the pointer to the next stop
    // Preconditions - Pointer has been defined
    // Postconditions - Updates m_next to next stop on Route
    void SetNextStop(Stop* newStop) {
        m_next = newStop;
    }

private:
    string m_name; //Name of the stop (train station)
    int m_number; //Number of the stop
    Stop *m_next; //Pointer to next stop
};

#endif
