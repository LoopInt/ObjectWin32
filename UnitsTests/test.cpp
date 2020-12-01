#include "pch.h"

#include "isolator.h"

#define protected public

#include "Window.h"
#include "Instance.h"
#include "File.h"
#include "Button.h"

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

TEST(Window, getClientWidth) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    RECT rect;
    rect.left = 50;
    rect.right = 250;
    rect.top = 50;
    rect.bottom = 145;

    AdjustWindowRect(
        &rect,
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_THICKFRAME | 
        WS_MINIMIZEBOX |
        WS_MAXIMIZEBOX,
        NULL
    );

    SetWindowPos(
        w.getHandle(),
        NULL,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        SWP_SHOWWINDOW
    );

    unsigned int clientWidth = w.getClientWidth();
    ASSERT_EQ(clientWidth, 200);
}

TEST(Window, getClientHeight) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    RECT rect;
    rect.left = 50;
    rect.right = 250;
    rect.top = 50;
    rect.bottom = 145;

    AdjustWindowRect(
        &rect,
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_THICKFRAME |
        WS_MINIMIZEBOX |
        WS_MAXIMIZEBOX,
        NULL
    );

    SetWindowPos(
        w.getHandle(),
        NULL,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        SWP_SHOWWINDOW
    );

    unsigned int clientHeight = w.getClientHeight();
    ASSERT_EQ(clientHeight, 95);
}

TEST(Window, setClientWidth) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setClientWidth(250);

    RECT rectClient;

    GetClientRect(w.hwnd, &rectClient);

    ASSERT_EQ(rectClient.right - rectClient.left, 250);
}

TEST(Window, setClientHeight) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setClientHeight(200);

    RECT rectClient;

    GetClientRect(w.hwnd, &rectClient);

    ASSERT_EQ(rectClient.bottom - rectClient.top, 200);
}

TEST(Window, setClientSize) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setClientSize(300, 200);

    RECT rectClient;

    GetClientRect(w.hwnd, &rectClient);

    ASSERT_EQ(rectClient.bottom - rectClient.top, 200);
    ASSERT_EQ(rectClient.right - rectClient.left, 300);
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

TEST(Window, setClientPosX) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    RECT rect;
    rect.left = 50;
    rect.right = 250;
    rect.top = 50;
    rect.bottom = 145;

    AdjustWindowRect(
        &rect,
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_THICKFRAME |
        WS_MINIMIZEBOX |
        WS_MAXIMIZEBOX,
        NULL
    );

    SetWindowPos(
        w.getHandle(),
        NULL,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        SWP_SHOWWINDOW
    );

    unsigned int clientPosX = w.getClientXPosition();
    ASSERT_EQ(clientPosX, 50);
}

TEST(Window, setClientPosY) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    RECT rect;
    rect.left = 50;
    rect.right = 250;
    rect.top = 50;
    rect.bottom = 145;

    AdjustWindowRect(
        &rect,
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_THICKFRAME |
        WS_MINIMIZEBOX |
        WS_MAXIMIZEBOX,
        NULL
    );

    SetWindowPos(
        w.getHandle(),
        NULL,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        SWP_SHOWWINDOW
    );

    unsigned int clientPosY = w.getClientXPosition();
    ASSERT_EQ(clientPosY, 50);
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

TEST(Window, isMaximizedWindow) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));
    w.show();

    ASSERT_EQ(w.isMaximized(), true);
}

TEST(Window, isMinimizedWindow) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));
    w.minimize();

    ASSERT_EQ(w.isMinimized(), true);
}

TEST(Window, setWidth) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setWidth(300);

    RECT rect;
    GetWindowRect(w.getHandle(), &rect);

    unsigned int width = rect.right - rect.left;

    ASSERT_EQ(width, 300);
}

TEST(Window, setHeight) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setHeight(400);

    RECT rect;
    GetWindowRect(w.getHandle(), &rect);

    unsigned int height = rect.bottom - rect.top;

    ASSERT_EQ(height, 400);
}

TEST(Window, setSize) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setSize(300, 400);

    RECT rect;
    GetWindowRect(w.getHandle(), &rect);

    unsigned int height = rect.bottom - rect.top;
    unsigned int width = rect.right - rect.left;

    ASSERT_EQ(width, 300);
    ASSERT_EQ(height, 400);
}

TEST(Window, setXPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setXPosition(400);

    RECT rect;
    GetWindowRect(w.getHandle(), &rect);

    ASSERT_EQ(rect.left, 400);
}

TEST(Window, setYPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setYPosition(200);

    RECT rect;
    GetWindowRect(w.getHandle(), &rect);

    ASSERT_EQ(rect.top, 200);
}

TEST(Window, setPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setPosition(400, 200);

    RECT rect;
    GetWindowRect(w.getHandle(), &rect);

    ASSERT_EQ(rect.left, 400);
    ASSERT_EQ(rect.top, 200);
}

TEST(Window, setClientXPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setClientXPosition(400);

    ASSERT_EQ(w.getClientXPosition(), 400);
}

TEST(Window, setClientYPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setClientYPosition(400);

    ASSERT_EQ(w.getClientYPosition(), 400);
}

TEST(Window, setClientPos) {
    Instance::init(GetModuleHandle(NULL));

    Window w;

    w.create(GetModuleHandle(NULL));

    w.setClientPosition(300, 400);

    ASSERT_EQ(w.getClientYPosition(), 400);
    ASSERT_EQ(w.getClientXPosition(), 300);
}

TEST(File, fileNotFound) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\lol.txt");

    ASSERT_EQ(fileFound, false);
}

TEST(File, fileFound) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\text.txt");

    ASSERT_EQ(fileFound, true);
}

TEST(File, readTextFile) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\text.txt");

    ASSERT_EQ(fileFound, true);

    std::string&& text = file.read();

    ASSERT_EQ(text, "hello world !");    
}

TEST(File, readFileDoesntOpen) {
    File file;

    ASSERT_THROW(file.read(), std::string);
}

TEST(File, getFileSize) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\text.txt");

    ASSERT_EQ(fileFound, true);

    unsigned long size = file.getSize();

    ASSERT_EQ(size, 13);
}

TEST(File, closeOpenedFile) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\text.txt");

    ASSERT_EQ(fileFound, true);

    ASSERT_EQ(file.close(), true);
}

TEST(File, closeClosedFile) {
    File file;

    ASSERT_EQ(file.close(), false);
}

TEST(File, readCharsFile) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\text.txt");

    ASSERT_EQ(fileFound, true);

    std::string&& text = file.readChars(5);

    ASSERT_EQ(text, "hello");
}

TEST(File, readCharsFileDoesntOpen) {
    File file;

    ASSERT_THROW(file.readChars(10), std::string);
}

TEST(File, getCursorPosition) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\text.txt");
    std::string&& text = file.readChars(5);
    unsigned long cursorPosition = file.getCursorPosition();

    ASSERT_EQ(cursorPosition, 5);
}

TEST(File, getCursorPositionWithCloseFile) {
    File file;

    ASSERT_THROW(file.getCursorPosition(), std::string);
}

TEST(File, setCursorPosition) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\text.txt");
    
    file.setCursorPosition(6);

    std::string&& text = file.readChars(5);

    ASSERT_EQ(text, "world");
}

TEST(File, moveCursorPositionPositive) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\text.txt");

    file.setCursorPosition(5);
    file.moveCursorPosition(2);    

    ASSERT_EQ(file.getCursorPosition(), 7);
}

TEST(File, moveCursorPositionNegative) {
    File file;

    bool fileFound = file.openReadOnly("E:\\Documents\\Projects\\ObjectWin32\\text.txt");

    file.setCursorPosition(5);
    file.moveCursorPosition(-2);

    ASSERT_EQ(file.getCursorPosition(), 3);
}