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

void Window::setClientWidth(unsigned int newWidth)
{
    RECT rectClient;
    
    if (!GetClientRect(this->hwnd, &rectClient)) {
        throw(GetLastError());
    }

    rectClient.right = 50 + newWidth;
    rectClient.left = 50;

    AdjustWindowRect(
        &rectClient,
        this->generateWindowStyle(),
        NULL
    );

    SetWindowPos(
        this->hwnd,
        NULL,
        0,
        0,
        rectClient.right - rectClient.left,
        rectClient.bottom - rectClient.top,
        SWP_NOMOVE
    );
}

void Window::setClientHeight(unsigned int newHeight)
{
    RECT rectClient;

    if (!GetClientRect(this->hwnd, &rectClient)) {
        throw(GetLastError());
    }

    rectClient.bottom = 50 + newHeight;
    rectClient.top = 50;

    AdjustWindowRect(
        &rectClient,
        this->generateWindowStyle(),
        NULL
    );

    SetWindowPos(
        this->hwnd,
        NULL,
        0,
        0,
        rectClient.right - rectClient.left,
        rectClient.bottom - rectClient.top,
        SWP_NOMOVE
    );
}

void Window::setClientSize(const unsigned int newWidth, const unsigned int newHeight)
{
    RECT rectClient;

    if (!GetClientRect(this->hwnd, &rectClient)) {
        throw(GetLastError());
    }

    rectClient.right = 50 + newWidth;
    rectClient.left = 50;
    rectClient.bottom = 50 + newHeight;
    rectClient.top = 50;

    AdjustWindowRect(
        &rectClient,
        this->generateWindowStyle(),
        NULL
    );

    SetWindowPos(
        this->hwnd,
        NULL,
        0,
        0,
        rectClient.right - rectClient.left,
        rectClient.bottom - rectClient.top,
        SWP_NOMOVE
    );
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

int Window::getClientXPosition() const
{
    RECT rect;
    rect.left = 50;
    rect.right = 250;
    rect.top = 50;
    rect.bottom = 145;

    AdjustWindowRect(
        &rect,
        this->generateWindowStyle(),
        NULL
    );

    unsigned int delta = 50 - rect.left;

    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }

    return rect.left + delta;
}

int Window::getClientYPosition() const
{
    RECT rect;
    rect.left = 0;
    rect.right = 250;
    rect.top = 0;
    rect.bottom = 250;

    AdjustWindowRect(
        &rect,
        this->generateWindowStyle(),
        NULL
    );

    unsigned int delta = - rect.top;

    if (!GetWindowRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }

    return rect.top + delta;
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

void Window::setClientXPosition(const int newPosX)
{
    RECT rect;

    if (!GetClientRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }

    rect.left = newPosX;

    AdjustWindowRect(
        &rect,
        this->generateWindowStyle(),
        NULL
    );   

    if (!SetWindowPos(this->hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}

void Window::setClientYPosition(const int newPosY)
{
    RECT rect;

    if (!GetClientRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }

    rect.top = newPosY;

    AdjustWindowRect(
        &rect,
        this->generateWindowStyle(),
        NULL
    );

    if (!SetWindowPos(this->hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOSIZE)) {
        throw(GetLastError());
    }
}

void Window::setClientPosition(const int newPosX, const int newPosY)
{
    RECT rect;

    if (!GetClientRect(this->hwnd, &rect)) {
        throw(GetLastError());
    }

    rect.top = newPosY;
    rect.left = newPosX;

    AdjustWindowRect(
        &rect,
        this->generateWindowStyle(),
        NULL
    );

    if (!SetWindowPos(this->hwnd, NULL, rect.left, rect.top, 0, 0, SWP_NOSIZE)) {
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

void Window::addChildrenWidget(const unsigned int id, ObjectWin32* newChild)
{
    this->childs[id] = newChild;
}

void Window::command(const unsigned int notif)
{
    return;
}

LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

    case WM_COMMAND:
        const unsigned int id = LOWORD(wParam);
        const unsigned int notif = HIWORD(wParam);
        this->childs[id]->command(notif);
        return true;
    }
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
