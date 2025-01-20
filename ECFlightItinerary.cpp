//
//  ECFlightItinerary.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

ECFlightItinerary :: ECFlightItinerary()
{
    flightSegments.clear();
}

bool ECFlightItinerary :: operator==(const ECFlightItinerary &rhs ) const
{
    if (GetNumSegments() != rhs.GetNumSegments() )
    {
        return false;
    } else {
        for (int i=0; i<GetNumSegments(); ++i )
        {
            if ( *GetSegment(i) != *rhs.GetSegment(i) )
            {
                return false;
            }
        }
    }
    return true;
}
// access/edit segments
// Return the number of segments of the itineary
int ECFlightItinerary :: GetNumSegments() const
{
    return flightSegments.size();
}
    
// Return a segment
ECFlight * ECFlightItinerary :: GetSegment(int segIndex) const
{
    return flightSegments[segIndex];
}
    
// Get flight time: from departure to arrival
double ECFlightItinerary :: GetFlightTime() const
{
    double totTime = 0;

    for (auto f : flightSegments)
    {
        totTime += f->flightTime();
    }

    return totTime;
}
    
// Get segment time: add the time of all segments
double ECFlightItinerary :: GetTimeAllSegments() const
{
    // not needed
    return -1;
}
    
// Get departure time
double ECFlightItinerary :: GetDepartTime() const
{
    return flightSegments[0]->GetDepartureTime();
}
    
// Get arrival time
double ECFlightItinerary :: GetArrivalTime() const
{
    return flightSegments[flightSegments.size()-1]->GetArrivalTime();
}
    
// Price 
double ECFlightItinerary :: GetPrice() const
{


    return 120.0 * GetFlightTime();
}

// add segment
void ECFlightItinerary :: addSegment(ECFlight *&f)
{
    for (int i=0; i<flightSegments.size(); ++i)
    {

        if (flightSegments[i]->GetSource() == f->GetSource() )
        {
            flightSegments.erase(flightSegments.begin()+i, flightSegments.end() );
            break;
        }
    }
    flightSegments.push_back(f);
}

// get final destination
ECFlight* ECFlightItinerary :: FinalDestination() const
{
    return GetSegment(flightSegments.size()-1 );
}

void ECFlightItinerary :: Dump() const
{
    cout << "----------------- Itinerary -----------------\n"<< endl;

    int i = 1;
    for (auto f : flightSegments)
    {
        cout << "Flight " << i << ": ";
        f->Dump();
        ++i;
    }
}