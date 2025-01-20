#include "ECAirport.h"
#include "ECAirlineOperation.h"
// #include "ECAirlineTicketing.h"
// #include "ECAirlineFinancial.h"
#include "ECFlightItinerary.h"
#include "ECAirlineSimulator.h"
#include "ECFlight.h"

#include "ECTextViewImp.h"
#include "ECConsoleUIView.h"
#include "ECConsoleUITextLabel.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUITextField.h"
#include "ECConsoleUIButton.h"
#include "ECConsoleFlightButton.h"

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

// function to add info to simulator from test file
void updateAirlineSimulator(ECAirlineSimulator *&sim, string &command, vector<string> &listAirports )
{
    
    // splitString(command, vec);
    stringstream ss(command);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vec(begin,end);

    if (vec[0] == "1" )
    {
        // cout << vec[1] << ", " << vec[2] << endl;
        sim->AddAirport( vec[2], vec[1] );
        listAirports.push_back(vec[1] );
    } else if (vec[0] == "2" ) {
        // cout << vec[1] << ", " << vec[2] << ", " << vec[3] << endl;
        sim->SetDistBtwAirports(vec[1], vec[2], stoi(vec[3]) );
    } else if (vec[0] == "3" ) {
        // cout << "3\n"; 
        sim->AddFlight(vec[1], vec[2], stof(vec[3]), stoi(vec[4]), stoi(vec[5]) );
    }
}


void readTestFile(ECAirlineSimulator *&sim, const string &filename, vector<string> &listAirports)
{
    ifstream testFile(filename);

    string line;

    if (testFile.is_open() )
    {
        while (getline(testFile, line) )
        {
            // cout << line << endl;
            if (line.front() == '#' || line.size() <=5)
            {
                continue;
            } else {
                updateAirlineSimulator(sim, line, listAirports);
            }
            
            
        }
        testFile.close();
    } else {
        cerr << "Unable to open file!!\n";
    }

}

void populateUI(ECConsoleUIView &viewTest, ECAirlineSimulator *&sim, vector<string> &listAirports)
{
    // create several labels
    ECConsoleUITextLabel *pl1 = new ECConsoleUITextLabel(15, 1, "Galaxy Airlines Flight Reservation System");
    pl1->SetHighlight(true);
    viewTest.AddUIItem(pl1);


    string horizBar;
    for(int i=0; i<viewTest.GetColNumInView(); ++i)
    {
        horizBar += '-';
    }

    
    ECConsoleUITextLabel *pl2 = new ECConsoleUITextLabel(0, 0, horizBar);
    viewTest.AddUIItem(pl2);
    ECConsoleUITextLabel *pl3 = new ECConsoleUITextLabel(0, viewTest.GetRowNumInView()-1, horizBar);
    viewTest.AddUIItem(pl3);


    // Add origin flights
    ECConsoleUITextLabel *pl4 = new ECConsoleUITextLabel(15, 3, "Origin");
    viewTest.AddUIItem(pl4);
    ECConsoleUIListBox *px1 = new ECConsoleUIListBox(15, 5, 30, 7 );

    for (auto x : listAirports )
    {
        px1->AddChoice( x );
    }
    px1->Choose(0);
    viewTest.AddUIItem(px1);



    // Add destination flights
    ECConsoleUITextLabel *pl5 = new ECConsoleUITextLabel(40, 3, "Destination");
    viewTest.AddUIItem(pl5);
    ECConsoleUIListBox *px2 = new ECConsoleUIListBox(40, 5, 55, 7 );
    for (auto x : listAirports )
    {
        px2->AddChoice( x );
    }
    px2->Choose(0);
    viewTest.AddUIItem(px2);    

    
    // itineraries
    ECConsoleUIListBox *px3 = new ECConsoleUIListBox(5, 14, viewTest.GetColNumInView()-1, 16 );
    px3->AddChoice("");
    // px3->Choose(0);
    

    ECConsoleUIView *tempView = &viewTest;
    // button to search for flights
    ECConsoleUIButton *pb1 = new ECConsoleFlightButton(25, 10, 50, 10, "Search for Flights", px1, px2, sim, /*tempView,*/ px3);
    viewTest.AddUIItem(pb1);
    viewTest.AddUIItem(px3); 




    // Flights label
    ECConsoleUITextLabel *pl6 = new ECConsoleUITextLabel(30, 12, "Flights");
    viewTest.AddUIItem(pl6);


    // Add a text field to input name
    ECConsoleUITextLabel *pl8 = new ECConsoleUITextLabel(15, 18, "Enter passenger name:");
    viewTest.AddUIItem(pl8);
    ECConsoleUITextField *pt1 = new ECConsoleUITextField(viewTest.GetView(), 15, 19, 20);
    viewTest.AddUIItem(pt1);

    
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Use: ./final <dataTestFile>\n";
        return -1;
    }
    ECAirlineSimulator sim;
    ECAirlineSimulator* psim = &sim;
    // ECAirlineSimulator *sim = new ECAirlineSimulator;
    vector<string> listAirports;
    readTestFile(psim, argv[1], listAirports);
// #if 0
    ECTextViewImp wndTest;
    // add a status bar
    wndTest.AddStatusRow("UI test", "For demo only", true);
    
    // Create a console UI view
    ECConsoleUIView viewUI(&wndTest);

    
    // Add a few UI items
    // BasicTestUI(viewUI);
    populateUI(viewUI, psim, listAirports);
    
    // Display it
    viewUI.Refresh();
    
    // Show the window
    try {
        wndTest.Show();
    }
    catch(std::string ex)
    {
        cout << "Exception: " << ex << endl;
    }
// #endif

    // ECAirlineOperation *op = sim->GetAirlineOp();

    // std::vector<ECFlight *> vec = op->getAllFlights();
    
    // for (auto x : vec)
    // {
    //     x->Dump();
    // }
    return 0;
}