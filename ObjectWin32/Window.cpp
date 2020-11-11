#include "Window.h"
#include "Instance.h"

Window::Window():
    label(L"ObjectWin32 Window"),
    parent(nullptr),
    minimizeButton(true)
{
}

Window::Window(Window* newParent):
    label(L"ObjectWin32 Window"),
    parent(newParent),
    minimizeButton(true)
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

void Window::disableMinimizeButton()
{
    this->minimizeButton = false;
}

void Window::enableMinimizeButton()
{
    this->minimizeButton = true;
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
        WS_THICKFRAME | 
        WS_MAXIMIZEBOX;

    if (this->minimizeButton) {
        windowStyle = windowStyle | WS_MINIMIZEBOX;
    }

    return windowStyle;
}
