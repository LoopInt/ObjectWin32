#include "MainWindow.h"
#include "Instance.h"
#include <thread>

void guiRun(HINSTANCE hInstance, MainWindow &w);

void test(int& i) {
    return;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow w;

    std::thread guiThread(guiRun, hInstance, std::ref(w));

    Sleep(1000);

    //unsigned int width = w.getWidth();
    //unsigned int height = w.getHeight();
    //unsigned int xPos = w.getXPosition();
    //unsigned int yPos = w.getYPosition();

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

    Instance::run();
}
