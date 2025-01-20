//
//  ECAirlineSimulator.hpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//  Simulate airline activities: booking, flights, etc

#ifndef ECAirlineSimulator_h
#define ECAirlineSimulator_h

#include <string>
#include <vector>
#include <set>
#include <map>

class ECAirlineOperation;
class ECAirlineTicketing;
class ECAirlineFinancial;
class ECFlightItinerary;
class ECFlight;

//****************************************************************************
// Airline simulator

class ECAirlineSimulator
{
public:
    ECAirlineSimulator();
    virtual ~ECAirlineSimulator();
    
    // *****************************************************
    // Configuration
    
    // Adding airport with name and IATA code
    void AddAirport(const std::string &name, const std::string &code);
    
    // Setup distaince between airport; note distance is symmetric: the distance from dest to src is the same as from src to dest
    void SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist);
    
    // Adding flights: src airport, dest airport, depart time, max number of passenger, operating cost
    void AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate );
    
    // Called to indicate no more flights to add
    void DoneFlightAdding() {};
    

    // *****************************************************
    // Flight search
    
    void PreferLowPrice() {};

    void PreferShortTime() {};

    void PreferEarlyArrival() {};

    // Search for flights; return all flights in listItineraries that go from src to dest
    void SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries )/*const*/;
    
    // Search for flights dfs algorithm
    void FlightsDFS(const int indy, const std::string &dest, const std::vector<ECFlight*> &allFlights, std::vector<ECFlight*> &path, std::vector<ECFlightItinerary> &listItineraries);
    // Set flight adjacency lists
    void SetAdjacencyList(const std::vector<ECFlight*> allFlights);

    // Set visited to false
    void ResetVisited(const std::vector<ECFlight*> allFlights);
    // Access airlines
    //ECAirlineFinancial *GetAirlineFin() { return pAirlineFin; }
    ECAirlineOperation *GetAirlineOp() { return pAirlineOp; }
    // ECAirlineTicketing *GetAirlineTicketing() { return pAirlineTicket; }
    
private:
    // initialize
    void Init();
    
    // key data member
    ECAirlineOperation *pAirlineOp;
    // ECAirlineFinancial *pAirlineFin;
    // ECAirlineTicketing *pAirlineTicket;
    std::map<int, bool> visited;
    std::map<int, std::vector<int> > adjList;
};


#endif /* ECAirlineSimulator_h */
