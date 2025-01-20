//
//  ECConsoleFlightButton.h
//  
//
//  Created by Yufeng Wu on 3/6/24.
//

#ifndef ECConsoleFlightButton_h
#define ECConsoleFlightButton_h

#include <string>
#include <vector>

#include "ECConsoleUIItem.h"
#include "ECConsoleUIListBox.h"
#include "ECAirlineSimulator.h"
#include "ECFlightItinerary.h"
#include "ECConsoleUIView.h"
#include "ECFlight.h"
#include "ECConsoleUIButton.h"


// class ECFlightItinerary;

//*****************************************************************************
// Console UI button: with a text and can be clicked

class ECConsoleFlightButton : public ECConsoleUIButton
{
public:
    // specifiy the portion of the view for this button and the text
    // ECConsoleUIButton(int xUL, int yUL, int xLR, int yLR, const std::string &textButton );
    ECConsoleFlightButton(int xUL, int yUL, int xLR, int yLR, const std::string &strButIn, ECConsoleUIListBox *&lb1in, ECConsoleUIListBox *&lb2in, ECAirlineSimulator *&simIn, /*ECConsoleUIView *&viewIn,*/ ECConsoleUIListBox *&lbOut );
    
    // Handle up key
    // Is responding to keys? YES: button handles keys!
    virtual bool IsHandlingKeys() const { return true; }
    // Handle enter key
    virtual void HdlKeyEnter();

    // put list of itineraries in dest vector, returns 1 if successful, 0 else
    int GetItineraries(std::vector<ECFlightItinerary> &dest) const;

    void populateFlights();
    
private:
    ECConsoleUIListBox *lb1;
    ECConsoleUIListBox *lb2;
    ECAirlineSimulator *sim;
    // ECConsoleUIView *view;
    ECConsoleUIListBox *lb;
    bool fReady;
    std::vector<ECFlightItinerary> itineraries;
    
};

#endif /* ECConsoleUIButton_h */
