#include <Windows.h>
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

    Sleep(10000);

    unsigned int width = w.getWidth();
    unsigned int height = w.getHeight();
    unsigned int xPos = w.getXPosition();

    guiThread.join();
    
    return 0;
}

void guiRun(HINSTANCE hInstance, MainWindow &w) {
    Instance::init(hInstance);

    w.create(hInstance);
    w.show();

    Instance::run();
}
