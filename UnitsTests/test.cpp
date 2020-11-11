#include "pch.h"

#include "isolator.h"

#include "Window.h"
#include "Instance.h"

TEST(Window, CreateWindow) {
    Instance::init(GetModuleHandle(NULL));

	Window w;
	FAKE_GLOBAL(CreateWindowEx);

    w.create(NULL);

	ASSERT_WAS_CALLED(CreateWindowEx(
        EQ(0),                              // Optional window styles.
        EQ(WindowClassName),                     // Window class
        EQ(L"ObjectWin32 Window"),    // Window text
        EQ(WS_OVERLAPPEDWINDOW),            // Window style
        // Size and position
        EQ(CW_USEDEFAULT), EQ(CW_USEDEFAULT), EQ(CW_USEDEFAULT), EQ(CW_USEDEFAULT),
        EQ(NULL),       // Parent window    
        EQ(NULL),       // Menu
        EQ(NULL),  // Instance handle
        EQ(&w)        // pointer to window (for windowProc redirection)
    ));
}

TEST(Window, CreateWindowFailedWithNullHandle) {
    Window w;
    FAKE_GLOBAL(CreateWindowEx);
    WHEN_CALLED(CreateWindowEx(
        EQ(0),                              // Optional window styles.
        EQ(WindowClassName),                     // Window class
        EQ(L"ObjectWin32 Window"),    // Window text
        EQ(WS_OVERLAPPEDWINDOW),            // Window style
        // Size and position
        EQ(CW_USEDEFAULT), EQ(CW_USEDEFAULT), EQ(CW_USEDEFAULT), EQ(CW_USEDEFAULT),
        EQ(NULL),       // Parent window    
        EQ(NULL),       // Menu
        EQ(NULL),  // Instance handle
        EQ(&w)        // pointer to window (for windowProc redirection)
    )).Return(NULL);

    try {
        w.create(NULL);
    }
    catch (std::string const& e) {
        std::string str = "Window creation failed.";
        ASSERT_EQ(e, str);
    }
}

TEST(Window, getWidth) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    SetWindowPos(
        w.getHandle(),
        NULL,
        50,
        75,
        300,
        250,
        SWP_SHOWWINDOW
    );

   unsigned int width = w.getWidth();
   ASSERT_EQ(width, 300);
}

TEST(Window, getHeight) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    SetWindowPos(
        w.getHandle(),
        NULL,
        50,
        75,
        300,
        250,
        SWP_SHOWWINDOW
    );

    unsigned int height = w.getHeight();
    ASSERT_EQ(height, 250);
}