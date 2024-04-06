/*****************************************************************
 * File: Passenger.cpp
 * Project: CMSC 202 Project 3, Fall 2020
 * Author: Nathan Wooddell
 * Date: 10/29/2020
 * Section: 10/30
 * E-mail: nathanw2@umbc.edu
 *
 * This class will hold all the data for each individual passenger,
 * members of this class will be loaded into vectors attached to
 * cars when the current stop is at their starting position.
 *
 *****************************************************************/

#include "Passenger.h"

//Passenger Constructor
Passenger::Passenger(string name, int age, string start, string final){
    m_fullName = name;
    m_age = age;
    m_startLocation = start;
    m_finalDestination = final;
}

//Returns the name of the passenger
string Passenger::GetName(){
    return m_fullName;
}
//Returns the start location of the passenger
string Passenger::GetStartLocation(){
    return m_startLocation;
}

//Return the final destination of the passenger as a string
string Passenger::GetFinalDestination(){
    return m_finalDestination;
}