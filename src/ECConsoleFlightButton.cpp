//
//  ECConsoleFlightButton.cpp
//  
//
//  Created by Isaiah Haynes on 5/1/24.
//

#include "ECConsoleFlightButton.h"

#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

//*****************************************************************************
// Console UI button: 

ECConsoleFlightButton :: ECConsoleFlightButton(int xUL, int yUL, int xLR, int yLR, const std::string &strButIn, ECConsoleUIListBox* &lb1in, ECConsoleUIListBox* &lb2in, ECAirlineSimulator *&simIn, /*ECConsoleUIView *&viewIn,*/ ECConsoleUIListBox *&lbOut ) : 
    ECConsoleUIButton(xUL, yUL, xLR, yLR, strButIn), lb1(lb1in), lb2(lb2in), sim(simIn), fReady(false), /*view(viewIn),*/ lb(lbOut)
{
    // not sure if lb1 and lb2 will be properly assigned. . .
    // same for sim
}

// Handle enter key
void ECConsoleFlightButton :: HdlKeyEnter()
{
    itineraries.clear();
    std::string src = lb1->ChosenString();
    std::string dest = lb2->ChosenString();
    fReady = false;
    if (src != dest)
    {
        // there's a problem with the simulation. . .
        // gets stuck in a loop
        sim->SearchForFlights(src, dest, itineraries);
    }

    if (itineraries.size() >= 1) fReady = true;
    // lb->RemoveChoices();
    populateFlights();
}

// put list of itineraries in dest vector, returns 1 if successful, 0 else
int ECConsoleFlightButton :: GetItineraries(std::vector<ECFlightItinerary> &dest) const
{
    if (fReady)
    {
        copy(itineraries.begin(), itineraries.end(), back_inserter(dest) );
        // may need to remove const func and set fReady to false
        // fReady = false;
        return 1;
    }
    return 0;
}

void ECConsoleFlightButton :: populateFlights()
{
    lb->RemoveChoices();
    if (fReady)
    {
        for (auto x : itineraries )
        {
            std::string label = "";
            for (int i=0; i < x.GetNumSegments(); ++i)
            {
                double time = x.GetSegment(i)->GetDepartureTime();
                char d[5];
                snprintf(d, 5, "%.1f", time);
                label += x.GetSegment(i)->GetSource() + " D: " + d + " -> ";
            }
            
            double time = x.FinalDestination()->GetArrivalTime();
            char a[5];
            snprintf(a, 5, "%.1lf", time);
            label += x.FinalDestination()->GetDest() + " A: " + a;
            lb->AddChoice( label );
        }

    } else {
        std::string label = "Error: No flights from " + lb1->ChosenString() + " to " + lb2->ChosenString();
        lb->AddChoice(label);
    }
    lb->Choose(0);

}