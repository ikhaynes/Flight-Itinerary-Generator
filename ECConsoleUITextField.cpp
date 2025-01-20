//
//  ECConsoleUITextField.cpp
//  
//
//  Created by Yufeng Wu on 5/24/23.
//

#include "ECConsoleUITextField.h"
#include "ECTextViewImp.h"
#include <iostream>
#include <unistd.h>

using namespace std;

ECConsoleUITextField :: ECConsoleUITextField(ECTextViewImp *pTextView, int xpos, int ypos, int len) :
    textView(pTextView), ECConsoleUIItem(xpos, ypos, xpos+len, ypos), strInput(": "), canEnterText(false)
{
}

string ECConsoleUITextField :: GetTextAtRow(int r) const
{
    string str;

    if ( r == GetYUL() )
    {
        str = strInput;
    }
    return str;
}

int ECConsoleUITextField :: GetHighlightPosition(int &xLeft, int &xRight) const
{
    xLeft = 0;
    xRight = GetWidth()-1;
    return 2;
}

void ECConsoleUITextField :: HdlKeyEnter()
{
    textView->SetCursorX(GetXUL() + strInput.size());
    textView->SetCursorY(GetYUL() );
    canEnterText = true;
}

void ECConsoleUITextField :: HdlOtherKey()
{
    if (canEnterText)
    {
        if (textView->GetPressedKey() == CTRL_C)
        {
            textView->SetCursorX(GetXUL() -1);
            textView->SetCursorY(GetYUL() );
            canEnterText = false;

        } else if (textView->GetPressedKey() == BACKSPACE)
        {
            RemoveText();
        } else if (textView->GetPressedKey() == ARROW_LEFT)
        {
            DecCursorX();
        } else if (textView->GetPressedKey() == ARROW_RIGHT)
        {
            IncCursorX();
        } else {
            AddText();
        }
    }
}

void ECConsoleUITextField :: AddText()
{
    if (textView->GetCursorX() < GetXLR() )
    {
        strInput += textView->GetPressedKey();
        IncCursorX();
    }
}

void ECConsoleUITextField :: RemoveText()
{
    if (strInput.size() > 2)
    {
        strInput = strInput.substr(0, strInput.size()-1);
        DecCursorX();
    }
}

void ECConsoleUITextField :: IncCursorX()
{
    if (textView->GetCursorX() < GetXLR() )
    {
        textView->SetCursorX(textView->GetCursorX() +1);
    }
}
void ECConsoleUITextField :: DecCursorX()
{
    if (textView->GetCursorX() > GetXUL()+2 )
    {
        textView->SetCursorX(textView->GetCursorX() -1);
    }
}