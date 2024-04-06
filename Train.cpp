/*****************************************************************
 * File: Train.cpp
 * Project: CMSC 202 Project 3, Fall 2020
 * Author: Nathan Wooddell
 * Date: 10/29/2020
 * Section: 10/30
 * E-mail: nathanw2@umbc.edu
 *
 * This file contains the Train.cpp and the linked list by the same
 * name. The file is used to add cars, and control the passengers on
 * the train. the number of passengers on each car is controlled by the
 * variable MAX_CAPACITY, (16 by default)
 *
 *****************************************************************/
#include "Train.h"

//Constructor for the train linked list
Train::Train(Route* inRoute){
    m_route = inRoute;
    m_totalCars = 0;
    m_head = nullptr;
    AddCar();

}

Train::~Train(){
    cout <<"TRAIN DECONSTRUCT!" << endl;
    Car *curr = m_head;
    //Cycles through the cars and deletes them to leave us with an empty list
    while(curr != nullptr){
        m_head = curr;
        curr = curr->m_next;
        cout << "<-- deleting car: " << m_head->m_carNumber << endl;
        //Outputs the deletion of a passenger from the vector they are contained in
        for(unsigned int i = 0; i < m_head->m_passengers.size();i++){
            cout << "Deleting Passenger: " << m_head->m_passengers.at(i)->GetName() << endl;
            delete m_head->m_passengers.at(i);
        }
        delete m_head;
    }
    delete curr;
    m_head = nullptr;
    m_totalCars = 0;
}

//Add a car to the train linked list.
void Train::AddCar(){
    Car* currCar = m_head;
    if(m_head == nullptr){
        //Creates the first car, the rest are handled by the else
        currCar = new Car(CAR_CAPACITY, m_totalCars);
        m_head = currCar;
    } else{
        //Will cycle through nodes until it reaches the end
        while(currCar->m_next != nullptr){
            currCar = currCar->m_next;
        }
        //Then places a new car at the end of the linked list
        currCar->m_next = new Car(CAR_CAPACITY, m_totalCars);
    }
    m_totalCars++;
}

//UNUSED will remove a car when the population of the car is zero and will delete it from the linked list
void Train::RemoveCar(Car* remCar){
    cout << "Removing Car" << endl;
    Car* compareCar = m_head;
    if(remCar == m_head){
        m_head = remCar->m_next;
        delete remCar;
    }else {
        while (compareCar != nullptr) {
            remCar->m_next = compareCar->m_next->m_next;
            delete remCar;
        }
    }
}

//Prints the status of the train
void Train::TrainStatus(){
    Car* currCar = m_head;
    int totalPass = 0;
    cout << "Printing Train Status Info" << endl;
    cout << "Total Cars: " << m_totalCars << endl;
    while(currCar != nullptr){
        //Gets the number of passengers on all cars
        totalPass += currCar->m_passengers.size();
        currCar = currCar->m_next;
    }
    cout << "Number of Passengers: "<< totalPass << endl;
    m_route->PrintRouteDetails();
}

//Loads the passengers from the file contained in passName.
void Train::LoadPassengers(string passName){
    string firstName, lastName, startLocation, finalLocation, fullName;
    int age;
    char junk;
    //Open and read from the file and assign to node in the linked list
    ifstream passenger;
    passenger.open(passName);
    while(passenger){
        //Gets the First Name
        getline(passenger, firstName, ',');

        //Gets the Last Name
        getline(passenger, lastName, ',');

        //Gets the Age, and clears the junk comma
        passenger >> age >> junk;

        //Gets the passenger's start location
        getline(passenger,startLocation, ',');

        //Gets the Passenger's Destination
        getline(passenger,finalLocation);

        //Creates the Fullname from "First Last"
        fullName = firstName.append(" ");
        fullName = fullName.append(lastName);

        //Boards passengers if their start location is where the train is.
        if(startLocation == m_route->GetCurrentStop()->GetName()){
            cout << "Passenger: " << fullName << " Added to train" << endl;
            Passenger* newPass = new Passenger(fullName,age,startLocation,finalLocation);
            //Loads the passengers onto the train
            BoardPassenger(newPass);
        }
    }
    cout << "------------------------------------------------------" << endl;
}

//Boards a passenger by adding them to the  first available spot, and if none exist a new car is added
void Train::BoardPassenger(Passenger* newPass){
    int run = 1;
    //Creates a car that will be used to iterate through the list
    Car* addedCar = m_head;
    //While loop will be killed by the availability of a spot on the train
    while (run == 1){
        if(IsTrainFull()){
            //Adds a new car if the train is completely full
            AddCar();
        }else{
            if(addedCar->IsFull()){
                addedCar = addedCar->m_next;
            }else{
                //Adds the passenger to the first available car
                addedCar->AddPassenger(newPass);
                run = 0;
            }
        }
    }
}

//Makes the passengers leave the train when they are at their final destination
void Train::DisembarkPassengers(){
    int remo = 0; //Tracks the number of passengers removed at a given stop
    Car* currCar = m_head; //a temp that will be used to move through the list

    //Starts at the car at the head of the train and iterates to the end
    while(currCar != nullptr){
        //Iterates passengers to find the one with a final location matching
        for(unsigned int i = 0; i < currCar->m_passengers.size(); i++){
            if(currCar->m_passengers.at(i)->GetFinalDestination() == m_route->GetCurrentStop()->GetName()){
                //Tracks the number of passengers removed.
                remo++;
                cout << currCar->m_passengers.at(i)->GetName() << " disembarks here." << endl;
		Passenger* delPass = currCar->m_passengers.at(i);
                currCar->m_passengers.erase(currCar->m_passengers.begin()+i);
		delete delPass;
            }
        }
        //Move to next node
        currCar = currCar->m_next;
    }
    if(remo == 0){
        cout << "No Passengers Disembarked!" << endl;
    }
}

//Moves to the next stop of the Route
void Train::TravelToNextStop(){
    //Checks to see if there is a next stop and will not move if there is not
    if(m_route->GetCurrentStop()->GetNextStop() == nullptr){
        cout << "You are at the end of the Light Rail Line, and cannot progress further!" << endl;
    }else{
        //Moves one node down the Route
        m_route->SetCurrentStop(m_route->GetCurrentStop()->GetNextStop());
        cout << "Moving to: " << m_route->GetCurrentStop()->GetName() << endl;
    }
}

//Reverses the route and turns the train around.
void Train::TurnTrainAround(){
    if(m_route->GetCurrentStop()->GetNextStop() == nullptr){
        m_route->ReverseRoute();
    }else{
        cout << "Train is not at the end of the line." << endl;
    }
}

//Checks to make sure that the train isn't full (used when boarding passengers)
bool Train::IsTrainFull(){
    Car* curr = m_head;
    //Enters the while loop and persists until
    while (curr != nullptr){
        //Will handle multiple cars.
        if(curr->m_passengers.size() == CAR_CAPACITY){
            //True if the current is m_head and there are no further nodes
            if(curr == m_head && m_head->m_next == nullptr){
                //Exits the function creating a new car.
                return true;
            } else{
                //Moves to next car if the first is full
                curr = curr->m_next;
            }
        //returns false if there is room in the car
        } else{
            return false;
        }
    }
    return true;
}
