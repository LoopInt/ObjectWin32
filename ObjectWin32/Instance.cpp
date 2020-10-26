#include "Instance.h"
#include "Window.h"

void Instance::init(HINSTANCE newhInstance)
{
    //Instance::hInstance = newhInstance;

    // Register the window class.
    WNDCLASSEXW wc = { };

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.lpfnWndProc = Window::RouterWindowProc;
    wc.hInstance = newhInstance;
    wc.lpszClassName = WindowClassName;

    RegisterClassEx(&wc);
}

void Instance::run()
{
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HINSTANCE Instance::getInstance()
{
    //return Instance::hInstance;
    return 0;
}
