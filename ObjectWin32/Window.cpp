#include "Window.h"
#include "Instance.h"

Window::Window():
    label(L"ObjectWin32 Window"),
    parent(nullptr),
    minimizeButton(true),
    maximizeButton(true)
{
}

Window::Window(Window* newParent):
    label(L"ObjectWin32 Window"),
    parent(newParent),
    minimizeButton(true),
    maximizeButton(true)
{
    
}

Window::~Window()
{
}

LRESULT Window::RouterWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_NCCREATE) {
        LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;
        SetWindowLong(hwnd, GWL_USERDATA, (long)cs->lpCreateParams);
    }

    Window* window = (Window*)GetWindowLong(hwnd, GWL_USERDATA);

    if (window) {
        // Redirect messages to the window procedure
        return window->WindowProc(hwnd, uMsg, wParam, lParam);
    }
    else {
        // Use default handling window procedure
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void Window::create(HINSTANCE hInstance)
{
    HWND parentHandle = NULL;
    if (this->parent) {
        parentHandle = this->parent->getHandle();
    }

    int windowStyle = this->generateWindowStyle();

    this->hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        WindowClassName,                     // Window class
        (LPCWSTR)this->label.c_str(),    // Window text
        windowStyle,            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        parentHandle,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        this        // pointer to window (for windowProc redirection)
    );

    if (this->hwnd == NULL) {
        throw std::string("Window creation failed.");
    }
}

void Window::show()
{
    ShowWindow(this->hwnd, true);
}

void Window::minimize()
{
    ShowWindow(this->hwnd, SW_MINIMIZE);
}

void Window::maximize()
{
    ShowWindow(this->hwnd, SW_MAXIMIZE);
}

bool Window::isMinimized() const
{
    return IsIconic(this->hwnd);
}

bool Window::isMaximized() const
{
    return !IsIconic(this->hwnd);
}

unsigned int Window::getWidth() const
{
    RECT rect;
    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }
    return rect.right - rect.left;
}

unsigned int Window::getHeight() const
{
    RECT rect;
    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }
    return rect.bottom - rect.top;
}

unsigned int Window::getClientWidth() const
{
    RECT rect;
    if (!GetClientRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }
    return rect.right;
}

unsigned int Window::getClientHeight() const
{
    RECT rect;
    if (!GetClientRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }
    return rect.bottom;
}

void Window::setWidth(unsigned int newWidth)
{
    RECT rect;
    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }

    if (!SetWindowPos(this->hwnd, NULL, 0, 0, newWidth, rect.bottom - rect.top, SWP_NOMOVE)) {
        throw(GetLastError());
    }
}

void Window::setHeight(unsigned int newHeight)
{
    RECT rect;
    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }

    if (!SetWindowPos(this->hwnd, NULL, 0, 0, rect.right - rect.left, newHeight, SWP_NOMOVE)) {
        throw(GetLastError());
    }
}

void Window::setSize(const unsigned int newWidth, const unsigned int newHeight)
{
    if (!SetWindowPos(this->hwnd, NULL, 0, 0, newWidth, newHeight, SWP_NOMOVE)) {
        throw(GetLastError());
    }
}

unsigned int Window::getXPosition() const
{
    RECT rect;
    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }
    return rect.left;
}

unsigned int Window::getYPosition() const
{
    RECT rect;
    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }
    return rect.top;
}

void Window::setXPosition(const unsigned int newPosX)
{
    RECT rect;
    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }

    if (!SetWindowPos(this->hwnd, NULL, newPosX, rect.top, 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}

void Window::setYPosition(const unsigned int newPosY)
{
    RECT rect;
    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }

    if (!SetWindowPos(this->hwnd, NULL, rect.left, newPosY, 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}

void Window::setPosition(const unsigned int newPosX, const unsigned int newPosY)
{
    if (!SetWindowPos(this->hwnd, NULL, newPosX, newPosY, 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}

void Window::disableMaximizeButton()
{
    this->maximizeButton = false;
    if (this->getHandle()) {
        this->updateStyle();
    }    
}

void Window::enableMaximizeButton()
{
    this->maximizeButton = true;
    if (this->getHandle()) {
        this->updateStyle();
    }
}

void Window::disableMinimizeButton()
{
    this->minimizeButton = false;
    if (this->getHandle()) {
        this->updateStyle();
    }
}

void Window::enableMinimizeButton()
{
    this->minimizeButton = true;
    if (this->getHandle()) {
        this->updateStyle();
    }
}

LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int Window::generateWindowStyle() const
{
    int windowStyle = WS_OVERLAPPED | 
        WS_CAPTION | 
        WS_SYSMENU | 
        WS_THICKFRAME;

    if (this->minimizeButton) {
        windowStyle = windowStyle | WS_MINIMIZEBOX;
    }

    if (this->maximizeButton) {
        windowStyle = windowStyle | WS_MAXIMIZEBOX;
    }

    return windowStyle;
}

void Window::updateStyle()
{
    SetWindowLongA(this->hwnd, GWL_STYLE, this->generateWindowStyle());
}
