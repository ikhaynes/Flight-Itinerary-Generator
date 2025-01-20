//
//  ECConsoleUIListBox.cpp
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#include "ECConsoleUIListBox.h"
#include <iostream>
using namespace std;

// specifiy the portion of the view for this list box
ECConsoleUIListBox :: ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR ) :
    ECConsoleUIItem(xUL, yUL, xLR, yLR), indexChoice(0), currRow(0),
    nRows(abs(GetYLR() - GetYUL() )+1), mult(1) { }
    
// Add a choice item
void ECConsoleUIListBox :: AddChoice(const std::string &text)
{
    choices.push_back(text);
}

void ECConsoleUIListBox :: RemoveChoices()
{
    // choices.erase(choices.begin()+1, choices.end() );
    choices.clear();
    indexChoice = 0;
    currRow = 0;
    mult = 1;
}
    
// Choose an item
void ECConsoleUIListBox :: Choose(int rIndex)
{
    currRow = rIndex;
}
    
// Get displayed text at a specific row
// Text is relative to the item portion (i.e., relative to (xLR, yLR))
std::string ECConsoleUIListBox :: GetTextAtRow(int r) const
{
    string str;
    int rconv = r - GetYUL();

    if( rconv <0 || /*rconv >= 1 ||*/ rconv >= GetHeight() )
    {
        return str;
    }

    if (currRow >= mult*nRows)
    {
        str += choices[rconv+(mult*nRows) ];
    } else {
        str += choices[rconv];
    }

    // ensure the str is not too long
    str = str.substr(0, GetWidth());
    return str;
}
    
// Get highlighted part (if any); return the row with highlight
// if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
// Assume: at most a single row with highlighted part
int ECConsoleUIListBox :: GetHighlightPosition(int &xLeft, int &xRight) const
{
    // if (fHighlight == false)
    // {
    //     return -1;
    // } else {
        xLeft = 0;
        xRight = GetWidth()-1;
        if (currRow >= nRows)
        {
            return currRow - mult*nRows;
        }
        return currRow;
    // }
}

// Handle up key
void ECConsoleUIListBox :: HdlKeyUp()
{
    if (currRow > 0)
    {
        --currRow;
    }

    if (currRow >= nRows)
    {
        mult = currRow / nRows;
    } else mult = 1;
}

// Handle down key
void ECConsoleUIListBox :: HdlKeyDown()
{
    if (currRow < choices.size()-1 )
    {
        ++currRow;
    }

    if (currRow >= nRows)
    {
        mult = currRow / nRows;
    } else mult = 1;
}