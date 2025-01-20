//
//  ECAirlineOperation.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//  About operation of an airline: especially flights management

#ifndef ECAirlineOperation_h
#define ECAirlineOperation_h

#include <set>
#include <string>
#include <vector>
#include <map>

class ECFlight;

// put your code about airline operation here...
class ECAirlineOperation {
public:
    ECAirlineOperation() {};

    virtual ~ECAirlineOperation();

    // Adding airport with name and IATA code
    void AddAirport(const std::string &name, const std::string &code);
    
    // Setup distaince between airport; note distance is symmetric: the distance from dest to src is the same as from src to dest
    void SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist);
    
    // Adding flights: src airport, dest airport, depart time, max number of passenger, operating cost
    void AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate );

    // return all flights
    std::vector<ECFlight*> getAllFlights() const;

private:
    // std::vector
    // std::vector<ECFlight*> *allFlights2;
    std::vector<ECFlight*> allFlights;
    std::vector<std::pair<ECFlight*, int> > flightCosts;

};

#endif
