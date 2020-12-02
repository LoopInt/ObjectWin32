#include "PushButton.h"
#include <string>

PushButton::PushButton(Window& newParent, const std::wstring& text):
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

PushButton::~PushButton()
{
}

void PushButton::setText(const std::wstring& text)
{
    SendMessage(
        this->hwnd,
        WM_SETTEXT,
        NULL,
        reinterpret_cast<LPARAM>(text.c_str())
    );
}

std::wstring PushButton::getText() const
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

int PushButton::getXPos() const
{
    RECT rectButton;
    if (!GetWindowRect(this->hwnd, &rectButton)) {
        throw(GetLastError());
    }

    return rectButton.left - this->parent.getClientXPosition();
}

int PushButton::getYPos() const
{
    RECT rectButton;
    if (!GetWindowRect(this->hwnd, &rectButton)) {
        throw(GetLastError());
    }

    return rectButton.top - this->parent.getClientYPosition();
}

void PushButton::setXPos(int newXPos)
{
    if (!SetWindowPos(this->hwnd, NULL, newXPos, this->getYPos(), 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}

void PushButton::setYPos(int newYPos)
{
    if (!SetWindowPos(this->hwnd, NULL, this->getXPos(), newYPos, 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}

void PushButton::setPos(int newXPos, int newYPos)
{
    if (!SetWindowPos(this->hwnd, NULL, newXPos, newYPos, 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}
