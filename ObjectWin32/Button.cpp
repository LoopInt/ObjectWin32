#include "Button.h"
#include <string>

Button::Button(Window& newParent, const std::wstring& text):
    parent(newParent)
{
    this->hwnd = CreateWindow(
        L"BUTTON",  // Predefined class; Unicode assumed 
        text.c_str(),      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        10,         // x position 
        10,         // y position 
        25,        // Button width
        20,        // Button height
        this->parent.getHandle(),     // Parent window
        NULL,       // No menu.
        NULL,
        NULL);
}

Button::~Button()
{
}

void Button::setText(const std::wstring& text)
{
    SendMessage(
        this->hwnd,
        WM_SETTEXT,
        NULL,
        reinterpret_cast<LPARAM>(text.c_str())
    );
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

int Button::getXPos() const
{
    RECT rectButton;
    if (!GetWindowRect(this->hwnd, &rectButton)) {
        throw(GetLastError());
    }

    return rectButton.left - this->parent.getClientXPosition();
}

int Button::getYPos() const
{
    RECT rectButton;
    if (!GetWindowRect(this->hwnd, &rectButton)) {
        throw(GetLastError());
    }

    return rectButton.top - this->parent.getClientYPosition();
}

void Button::setXPos(int newXPos)
{
    if (!SetWindowPos(this->hwnd, NULL, newXPos, this->getYPos(), 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}

void Button::setYPos(int newYPos)
{
    if (!SetWindowPos(this->hwnd, NULL, this->getXPos(), newYPos, 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}

void Button::setPos(int newXPos, int newYPos)
{
    if (!SetWindowPos(this->hwnd, NULL, newXPos, newYPos, 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}
