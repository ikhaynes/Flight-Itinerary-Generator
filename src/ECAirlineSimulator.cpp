//
//  ECAirlineSimulator.cpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//

#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
// #include "ECAirlineTicketing.h"
// #include "ECAirlineFinancial.h"
#include "ECAirport.h"
#include "ECFlight.h"
#include "ECFlightItinerary.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

ECAirlineSimulator :: ECAirlineSimulator()
{
    pAirlineOp = new ECAirlineOperation;
}

ECAirlineSimulator :: ~ECAirlineSimulator()
{
    // delete pAirlineFin;
    delete pAirlineOp;
    // delete pAirlineTicket;
}

// Adding airport with name and IATA code
void ECAirlineSimulator :: AddAirport(const std::string &name, const std::string &code)
{
    // cout << "Adding airport " << name << endl;
    ECAirportInfo::Instance().CreateAirport(name, code);
}

    // Setup distaince between airport; note distance is symmetric: the distance from dest to src is the same as from src to dest
void ECAirlineSimulator :: SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist)
{
    // cout << "Setting distance between " << srcAirport << " and " << destAirport << endl;
    ECAirportInfo::Instance().SetDistanceBtw(srcAirport, destAirport, dist);
    ECAirportInfo::Instance().SetDistanceBtw(destAirport, srcAirport, dist);
}

    // Adding flights: src airport, dest airport, depart time, max number of passenger, operating cost
void ECAirlineSimulator :: AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate )
{
    
    pAirlineOp->AddFlight(srcAirport, destAirport, tmDepart, maxPassengers, costOperate);

}

// Searcch for flights; return all flights in listItineraries that go from src to dest
void ECAirlineSimulator :: SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries ) //const
{
    cout << endl << "Searching for flights from " << src << " to " << dest << endl;
    cout << endl;

    vector<ECFlight*> flights = pAirlineOp->getAllFlights();
    ResetVisited(flights);
    SetAdjacencyList(flights);

    
    for (int i=0; i<flights.size(); ++i)
    {
        if (flights[i]->GetSource() == src )
        {
            vector<ECFlight*> path;
            FlightsDFS(i, dest, flights, path, listItineraries);
        }
    }

    for (int i=0; i<listItineraries.size(); ++i)
    {
        for (int j=0; j<listItineraries.size(); ++j)
        {
            if (listItineraries[i] == listItineraries[j] && i != j)
            {
                listItineraries.erase(listItineraries.begin()+j);
            }
        }
    }
    cout << endl;
}

// Search for flights dfs algorithm
void ECAirlineSimulator :: FlightsDFS(const int indy, const string &dest, const std::vector<ECFlight*> &allFlights, vector<ECFlight*> &path, std::vector<ECFlightItinerary> &listItineraries)
{
    visited[indy] = true;
    
    // fix error where function adds an item to the path where
    // the source of current flight doesn't equal the destination of previous flight
    if (path.size() > 1)
    {
        while (path[path.size()-1]->GetDest() != allFlights[indy]->GetSource() )
        {
            path.pop_back();
        }
    }
    path.push_back(allFlights[indy]);

    // check if reached proper destination
    if (allFlights[indy]->GetDest() == dest)
    {

        ECFlightItinerary itinerary;
        for (auto f : path)
        {
            itinerary.addSegment(f);
        }
        visited[indy] = false;
        // path.pop_back();
        listItineraries.push_back(itinerary);
    } else {
        vector<int>::iterator i;
        for (i = adjList[indy].begin(); i != adjList[indy].end(); ++i )
        {
            if (!visited[*i] )
            {
                FlightsDFS(*i, dest, allFlights, path, listItineraries);
            } 
        }
    }
}

// Set flight adjacency lists
void ECAirlineSimulator :: SetAdjacencyList(const vector<ECFlight*> allFlights)
{
    for (int i=0; i<allFlights.size(); ++i)
    {
        vector<int> flightIndices;

        ECFlight* curr = allFlights[i];

        for (int j=0; j<allFlights.size(); ++j)
        {
            ECFlight* next = allFlights[j];
            if (curr->GetDest() == next->GetSource() && 
                curr->GetArrivalTime() <= next->GetDepartureTime() )
            {
                flightIndices.push_back(j);
            }
        }
        adjList[i] = flightIndices;
    }
}

// Set visited to false
void ECAirlineSimulator :: ResetVisited(const std::vector<ECFlight*> allFlights)
{
    for (int i=0; i<allFlights.size(); ++i)
    {
        visited[i] = false;
    }
}