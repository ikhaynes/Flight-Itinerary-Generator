//
//  ECConsoleUIListBox.h
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#ifndef ECConsoleUIListBox_h
#define ECConsoleUIListBox_h

#include <string>
#include <vector>

#include "ECConsoleUIItem.h"
#include "ECConsoleUITextLabel.h"

//*****************************************************************************
// Console UI list box: several rows (items) to choose from

class ECConsoleUIListBox : public ECConsoleUIItem
{
public:
    // specifiy the portion of the view for this list box
    ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR );

    ~ECConsoleUIListBox() {};
    
    // Add a choice item
    void AddChoice(const std::string &text);

    void RemoveChoices();
    
    // Choose an item
    void Choose(int rIndex);
    
    // Get the chosen one // not sure what this is for, I'm not using it at all
    int GetChoice() const { return indexChoice; }
    
    // Get displayed text at a specific row
    // Text is relative to the item portion (i.e., relative to (xLR, yLR))
    virtual std::string GetTextAtRow(int r) const;
    
    // Get highlighted part (if any); return the row with highlight
    // if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
    // Assume: at most a single row with highlighted part
    virtual int GetHighlightPosition(int &xLeft, int &xRight) const;

    // Are there any other function you might need to override?

    std::string ChosenString() const { return choices[currRow]; }
    // respond to keys
    virtual bool IsHandlingKeys() const { return true; }

    // Handle up key
    virtual void HdlKeyUp();

    // Handle down key
    virtual void HdlKeyDown();

    
    
private:
    // bool fHighlight;
    int indexChoice, currRow, nRows, mult;
    std::vector<std::string> choices;
};

#endif /* ECConsoleUIListBox_h */
