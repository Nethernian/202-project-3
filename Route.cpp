/*****************************************************************
 * File: Route.cpp
 * Project: CMSC 202 Project 3, Fall 2020
 * Author: Nathan Wooddell
 * Date: 10/29/2020
 * Section: 10/30
 * E-mail: nathanw2@umbc.edu
 *
 * This File contains the route class that creates the route used and
 * and taken by the Train.cpp class. It also creates a linked list
 * called Route, this contains all the stops read from the file:
 * proj3_routes.txt
 *
 *****************************************************************/

#include "Route.h"

//The Default Constructor for the linked list
Route::Route(){
    //Will set m_head and m_tail to nullptr to allow the route to be created
    m_head = nullptr;
    m_tail = nullptr;
    m_totalStops = 0;
    m_currentStop = nullptr;
}

//The De-constructor for the Route
Route::~Route(){
    //Deconstruct by moving through the nodes and deleting them
    Stop *curr = m_head;
    while(curr != nullptr){
        m_head = curr;
        curr = curr->GetNextStop();
        cout << "deleting stop: " << m_head->GetName() << endl;
        delete m_head;
    }
    m_head = nullptr; //Returns m_head to nullptr
    m_tail = nullptr; //Returns m_tail to nullptr
    m_totalStops = 0; //Returns m_totalStops to zero
    m_currentStop = nullptr; //Returns m_currentStop to nullptr
}

//Loads route from the file name contained by fileName (by default: proj3_routes.txt)
void Route::LoadRoute(string fileName){
    string stopText;
    int stopNum;
    string junk;

    //Open and read from the file and assign to node in the linked list
    ifstream routes;
    routes.open(fileName);

    //Keeps the reading within the file
    while(routes){
        //Gets the Stop Name until the comma
        getline(routes, stopText, ',');

        //Gets the Stop Number
        routes >> stopNum;

        //Clears the rest of the Line
        getline(routes, junk);

        //Calls to AddStop (Route.cpp : Line 64)
        AddStop(stopText, stopNum);
    }
    //Closes the routes file
    routes.close();
    //Resets to top of linked list
    m_currentStop = m_head;
}

//Inserts a new stop to the end of the linked list
void Route::AddStop(string stopName, int stopNum){
    if(m_currentStop == nullptr){
        //Creates the first stop in the route
        Stop* newStop = new Stop(stopName, stopNum);
        newStop->SetNextStop(nullptr); //Sets the next to the nullptr;

        //Sets the head and tail node, the tail will be moved later.
        m_head = newStop; //this will be the first stop forever
        m_tail = newStop;
        m_currentStop = newStop; //makes the current stop no longer nullptr

    } else {
        //Creates Subsequent stops in the route
        Stop* newStop = new Stop(stopName, stopNum);
        m_currentStop->SetNextStop(newStop);

        //Sets the tail, the head will be the same
        m_tail = newStop;
        m_currentStop = newStop;
        m_currentStop->SetNextStop(nullptr);
    }
    //Increments the total stops
    m_totalStops++;
    //To be deleted later!
    cout << "Stop: " << stopName << " added at position: " << m_totalStops << endl;
}

//Prints the details of the route to the console
void Route::PrintRouteDetails(){
    if(m_totalStops == 0) {
        //Ensures that there are stops in the Route
        cout << "No Nodes to Display (STOPS)" << endl;

    }else if(m_head == nullptr){
        //Ensures that the head has been created for the linked list
        cout << "No Nodes to Display (HEAD-NULL)" << endl;

    }else if(m_currentStop != nullptr){
        //Display the location of the train, and the stop number
        cout << "Currently at: "<< GetCurrentStop()->GetName() << ", ";
        cout << GetCurrentStop()->GetNumber() << endl;
    }
}

//Returns m_currentStop
Stop* Route::GetCurrentStop(){
    return m_currentStop;
}

//Sets the current stop, used to move the route while outside of it's scope
void Route::SetCurrentStop(Stop* newStop){
    //Iterate through the linked list until newStop == m_currentStop
    while(m_currentStop->GetName() != newStop->GetName()){
        //Calls GetNextStop() (Stop.cpp : Line 50)
        m_currentStop = newStop;
    }
}

//Reverses the route and cleans up the route used to reverse it
void Route::ReverseRoute(){
    //Check if the rout is at the end
    if(m_currentStop != m_tail){
        cout << "You are not at the end of the route, and cannot turn around!" << endl;
        return;
    }else{
        Route* newRoute = new Route();
        Stop* curr;
        Stop* newCurr;
        //Sets the route to start at m_tail and will work backwards.
        newRoute->m_head = m_tail;
        curr = m_head;
        newCurr = newRoute->m_head;
        //Since m_head is set, m_totalStops-1 will need to run every time
        for(int i = 0; i < m_totalStops-1; i++){
            //Will move to the next stop unless we reach the end.
            while (curr->GetNextStop()->GetNextStop() != nullptr){
                curr = curr->GetNextStop();
            }
            //Resets the loop, and changes
            newCurr->SetNextStop(curr);
            newCurr = newCurr->GetNextStop();
            newCurr->SetNextStop(nullptr);
            curr->SetNextStop(nullptr);
            curr = m_head;
        }
        //Resets the Route to be newRoute
        m_head = newRoute->m_head;
        m_tail = newRoute->m_tail;
        //Prepares the newRoute for deletion (so it doesn't take Route with it)
        newRoute->m_head = nullptr;
        newRoute->m_tail = nullptr;;
        newRoute->m_currentStop = nullptr;
        newRoute->m_totalStops = 0;
        //Delete the newRoute memory to prevent leaks
        delete newRoute;
    }

}