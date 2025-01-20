//
//  ECFlight.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlight_h
#define ECFlight_h

#include <string>


// ****************************************************************************
// Flight: service between two airports at a specific time;

class ECFlight
{
public:
    ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn);

    ECFlight& operator=(const ECFlight &f);

    bool operator==(const ECFlight &other) const;

    bool operator!=(const ECFlight &other) const;

    virtual ~ECFlight();
    
    // Get departure time
    double GetDepartureTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Set max passenger for this flight
    void SetMaxNumPassengers(int m);
    
    // Get number of passengers
    int GetMaxPassengers() const;
    // Get src airport code
    std::string GetSource() const;
    
    // Get destination code
    std::string GetDest() const;

    double flightTime() const;

    // Dump all info
    void Dump() const;
    // more to add...    

private:
    std::string srcIn;
    std::string destIn;
    double tmDepartIn;
    int maxPassengersIn;
};

#endif /* ECFlight_h */
