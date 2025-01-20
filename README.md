# Airline-Reservation-System-CSE3150

## Basic Instructions
CTRL+Q quit

CTRL+A cycle to next option

use arrows for origin + Destination + Flights

Enter for search for flights & enter name

## Run Simulator

The above command will build an executable that can be run by using the following line: ./airlineSim dataTestFile

An easier way of compiling the code can be accomplished by typing `make` or `make airlineSim` in the command line. With the included Makefile, this will automatically compile the programm with the first command.


## Photos


## Known issues/bugs

There are various known bugs in the program in its current state. 

First, the list boxes sometimes show information from the next list box on the screen. However, even though items from another list box are shown, they are not selectable from within the list box where they should not be shown.
    This error appears to only show up on MacOS M1 (this error did not show up when tested with Ubuntu OS in VMware Fusion)

The second bug is that the list box that contains the itineraries will sometimes show more than the rows that were added to it. This may include duplicate rows, or extra rows that include random characters.

The final known issue is that after a period of time cycling through the UI items, the program may crash with a memory error. This error appears to only show on MacOS with M1 (not tested in Windows or other MacOS devices) as running this program with Ubuntu in VMware Fusion does not produce this error.