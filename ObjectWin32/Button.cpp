#include "Button.h"
#include <string>

Button::Button(ObjectWindow& parent, const std::wstring& text)
{
    this->hwnd = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        text.c_str(),      // Button text 
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

std::wstring Button::getText() const
{
    const int size = 80;
    wchar_t buffer[size] = L"";

    SendMessage(
        this->hwnd,
        WM_GETTEXT,
        size,
        reinterpret_cast<LPARAM>(buffer)
    );

    return std::wstring(buffer);
}