//
//  ECAirlineOperation.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirlineOperation.h"
#include "ECFlightItinerary.h"
// #include "ECAirlineFinancial.h"
#include "ECAirport.h"
#include "ECFlight.h"

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

ECAirlineOperation :: ~ECAirlineOperation()
{
    for (auto x : allFlights)
    {
        delete x;
    }
}

// Adding flights: src airport, dest airport, depart time, max number of passenger, operating cost
void ECAirlineOperation :: AddFlight(const string &srcAirport, const string &destAirport, double tmDepart, int maxPassengers, double costOperate )
{
    ECFlight *f = new ECFlight(srcAirport, destAirport, tmDepart, maxPassengers);
    // cout << "Adding flight from ";
    // f->Dump();
    
    allFlights.push_back(f);
    flightCosts.push_back(make_pair(f, costOperate) );
    // cout << "Added flight\n";
}

// return all flights
vector<ECFlight*> ECAirlineOperation :: getAllFlights() const
{
    return allFlights;
}