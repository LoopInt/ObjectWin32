#include "MainWindow.h"
#include "Instance.h"
#include "Button.h"
#include <thread>

void guiRun(HINSTANCE hInstance, MainWindow &w);

void test(int& i) {
    return;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow w;

    std::thread guiThread(guiRun, hInstance, std::ref(w));

    Sleep(2000);

    //w.minimize();

    //unsigned int width = w.getWidth();
    //unsigned int height = w.getHeight();
    //unsigned int xPos = w.getXPosition();
    //unsigned int yPos = w.getYPosition();

    //w.setWidth(500);
    //w.setHeight(500);
    w.setSize(500, 400);

    guiThread.join();
    
    return 0;
}

void guiRun(HINSTANCE hInstance, MainWindow &w) {
    Instance::init(hInstance);

    //w.disableMinimizeButton();
    //w.enableMinimizeButton();

    //w.disableMaximizeButton();
    //w.enableMinimizeButton();

    w.create(hInstance);
    w.show();
    Button b(w, L"OK");

    b.setXPos(50);

    Instance::run();
}
