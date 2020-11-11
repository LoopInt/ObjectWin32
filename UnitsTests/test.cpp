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

TEST(Window, getPosX) {
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

    unsigned int posX = w.getXPosition();
    ASSERT_EQ(posX, 50);
}

TEST(Window, getPosY) {
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

    unsigned int posY = w.getYPosition();
    ASSERT_EQ(posY, 75);
}

TEST(Window, disableMinimizeButton) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.disableMinimizeButton();

    w.create(GetModuleHandle(NULL));

    long windowStyle = GetWindowLongA(w.getHandle(), GWL_STYLE);
    ASSERT_EQ((bool) (windowStyle & WS_MINIMIZEBOX), false);
}

TEST(Window, enableMinimizeButton) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.disableMinimizeButton();
    w.enableMinimizeButton();

    w.create(GetModuleHandle(NULL));

    long windowStyle = GetWindowLongA(w.getHandle(), GWL_STYLE);
    ASSERT_EQ((bool)(windowStyle & WS_MINIMIZEBOX), true);
}

TEST(Window, disableMaximizeButton) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.disableMaximizeButton();

    w.create(GetModuleHandle(NULL));

    long windowStyle = GetWindowLongA(w.getHandle(), GWL_STYLE);
    ASSERT_EQ((bool)(windowStyle & WS_MAXIMIZEBOX), false);
}

TEST(Window, enableMaximizeButton) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.disableMaximizeButton();
    w.enableMaximizeButton();

    w.create(GetModuleHandle(NULL));

    long windowStyle = GetWindowLongA(w.getHandle(), GWL_STYLE);
    ASSERT_EQ((bool)(windowStyle & WS_MAXIMIZEBOX), true);
}

TEST(Window, disableMinimizeButtonAfterCreation) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.disableMinimizeButton();

    long windowStyle = GetWindowLongA(w.getHandle(), GWL_STYLE);
    ASSERT_EQ((bool)(windowStyle & WS_MINIMIZEBOX), false);
}

TEST(Window, enableMinimizeButtonAfterCreation) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.disableMinimizeButton();

    w.create(GetModuleHandle(NULL));

    w.enableMinimizeButton();

    long windowStyle = GetWindowLongA(w.getHandle(), GWL_STYLE);
    ASSERT_EQ((bool)(windowStyle & WS_MINIMIZEBOX), true);
}

TEST(Window, disableMaximizeButtonAfterCreation) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.disableMaximizeButton();

    long windowStyle = GetWindowLongA(w.getHandle(), GWL_STYLE);
    ASSERT_EQ((bool)(windowStyle & WS_MAXIMIZEBOX), false);
}

TEST(Window, enableMaximizeButtonAfterCreation) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.disableMaximizeButton();

    w.create(GetModuleHandle(NULL));

    w.enableMaximizeButton();

    long windowStyle = GetWindowLongA(w.getHandle(), GWL_STYLE);
    ASSERT_EQ((bool)(windowStyle & WS_MAXIMIZEBOX), true);
}

TEST(Window, minimizeWindow) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.minimize();

    ASSERT_EQ(IsIconic(w.getHandle()), true);
}

TEST(Window, maximizeWindow) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.minimize();
    w.maximize();

    ASSERT_EQ(IsIconic(w.getHandle()), false);
}