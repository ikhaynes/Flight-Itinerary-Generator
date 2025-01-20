final:
	g++ ECConsoleUITextLabel.cpp ECTextViewImp.cpp ECConsoleUIView.cpp ECConsoleUIListBox.cpp ECConsoleUITextField.cpp ECConsoleUIButton.cpp ECConsoleFlightButton.cpp ECAirlineFinancial.cpp ECAirlineOperation.cpp ECAirlineSimulator.cpp ECAirlineTicketing.cpp ECAirport.cpp ECFlight.cpp ECFlightItinerary.cpp CompleteTest.cpp -std=c++11 -o final
	
ui:
	g++ ECConsoleUITextLabel.cpp ECTextViewImp.cpp ECConsoleUIView.cpp ECConsoleUIListBox.cpp ECConsoleUITextField.cpp ECConsoleUIButton.cpp ECConsoleUITest.cpp -std=c++11 -o ui

airport:
	g++ ECAirlineSimulator.cpp ECFlight.cpp ECAirlineFinancial.cpp ECAirlineTicketing.cpp ECFlightItinerary.cpp ECAirlineOperation.cpp ECAirport.cpp ECAirSimTest-part1.cpp -std=c++11 -o airport

clean:
	rm -f test airport final ui
