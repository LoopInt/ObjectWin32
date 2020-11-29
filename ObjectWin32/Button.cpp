#include "Button.h"

Button::Button(ObjectWindow& parent)
{
    this->hwnd = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        L"OK",      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        10,         // y position 
        25,        // Button width
        20,        // Button height
        parent.getHandle(),     // Parent window
        NULL,       // No menu.
        NULL,
        NULL);
}

Button::~Button()
{
}
