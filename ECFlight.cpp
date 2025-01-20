//
//  ECFlight.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlight.h"
#include "ECAirport.h"

#include <iostream>
using namespace std;

// ****************************************************************************

ECFlight :: ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn) :
    srcIn(srcIn), destIn(destIn), tmDepartIn(tmDepartIn), maxPassengersIn(maxPassengersIn) {}

ECFlight& ECFlight :: operator=(const ECFlight &f)
{
    srcIn = f.GetSource();
    destIn = f.GetDest();
    tmDepartIn = f.GetDepartureTime();
    maxPassengersIn = f.maxPassengersIn;
    return *this;
}

bool ECFlight :: operator==(const ECFlight &other) const
{
    if (srcIn == other.GetSource() && destIn == other.GetDest() &&
        tmDepartIn == other.GetDepartureTime() && maxPassengersIn == other.GetMaxPassengers() )
    {
        return true;
    }
    return false;
}

bool ECFlight :: operator!=(const ECFlight &other) const
{
    return !(*this == other);
}

ECFlight :: ~ECFlight()
{

}

// Get departure time
double ECFlight :: GetDepartureTime() const
{
    return tmDepartIn;
}

// Get arrival time
double ECFlight :: GetArrivalTime() const
{
    double time = ECAirportInfo::Instance().GetDistanceBtw(srcIn, destIn) / 500.0;

    // if (srcIn == "EWR" && destIn == "ORD")
    // {
    //     cout << "time is " << time << endl;
    // }

    return time + tmDepartIn;
}

// set max passengers
void ECFlight :: SetMaxNumPassengers(int m)
{
    maxPassengersIn = m;
}

// Get number of passengers
int ECFlight :: GetMaxPassengers() const
{
    return maxPassengersIn;
}

// Get src airport code
string ECFlight :: GetSource() const
{
    return srcIn;
}

string ECFlight :: GetDest() const
{
    return destIn;
}

double ECFlight :: flightTime() const
{
    // this will probably be an error if time is not in 24 hour format
    double t = GetArrivalTime() - GetDepartureTime();
    return t;
}

void ECFlight :: Dump() const
{
    cout << srcIn << " -> " << destIn << endl;
    cout << "Departure: " << GetDepartureTime() << " Arrival: " << GetArrivalTime() << endl;
    cout << "Max # passengers: " << maxPassengersIn << endl;
    cout << endl;

}