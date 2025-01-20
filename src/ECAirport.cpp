//
//  ECAirport.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirport.h"

#include <algorithm>
#include <set>

using namespace std;
// ****************************************************************************
// Airport: start/end point of a flight

// by default, airport is operating (except in default constructor)
ECAirport :: ECAirport(): name(""), codeIATA(""), operating(false) {}

ECAirport :: ECAirport(const string &nameAP, const string &codeIATA) :
    name(nameAP), codeIATA(codeIATA), operating(true) {}

ECAirport :: ECAirport(const ECAirport &rhs) : 
    name(rhs.GetName()), codeIATA(rhs.GetCode()), operating(rhs.IsOperating()) {}

// Get the name of the airport
string ECAirport :: GetName() const
{
    return name;
}

// Get IATA code
std::string ECAirport :: GetCode() const
{
    return codeIATA;
}

// Operating status: is it operating normally?
bool ECAirport :: IsOperating() const
{
    return operating;
}

// Set operating status
void ECAirport :: SetOperating(bool f)
{
    operating = f;
}


// ****************************************************************************
// Airport info: access airport information
// Use singleton pattern

// create instance
ECAirportInfo& ECAirportInfo :: Instance()
{
    static ECAirportInfo instance;
    return instance;    
}

ECAirportInfo :: ~ECAirportInfo()
{
}

// Create a new airport in the system
void ECAirportInfo :: CreateAirport(const string &name, const string &code)
{
    ECAirport ap = ECAirport(name, code);

    airports.insert(&ap);

}

ECAirport &ECAirportInfo :: GetAirport(const string &code) const
{
    auto it = airports.end();

    for( ECAirport* x: airports )
    {
        if (x->GetCode() == code )
        {
            return *x;
            break;
        }
    }

    throw invalid_argument( "Airport not found" );
}

void ECAirportInfo :: SetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code, int dist)
{   
    distances[make_pair(ap1Code, ap2Code)] = dist;
}

double ECAirportInfo :: GetDistanceBtw(const std::string &ap1Code, const std::string &ap2Code) const
{
    try {
        // may need to change below to just int instead of int&
        const int& dist = distances.at(make_pair(ap1Code, ap2Code) );
        // cout << "Distance between " << ap1Code << " and " << ap2Code << " is " << dist << endl;
        return dist;
    }
    catch (const out_of_range&) {
        cout << "Airports not found\n";
        return -1;
    }
    // return distances.at(make_pair(ap1Code, ap2Code) );
}

// void ECAirportInfo :: getAllAirports(std::vector<ECAirport *> &dest) const
// {
//     // copy(airports.begin(), airports.end(), back_inserter(dest) );
//     // CreateAirport("TTT", "test");
//     dest.push_back(*airports.begin());
// }