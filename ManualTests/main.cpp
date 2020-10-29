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

    Sleep(1000);

    unsigned int i = w.getWidth();

    guiThread.join();
    
    return 0;
}

void guiRun(HINSTANCE hInstance, MainWindow &w) {
    Instance::init(hInstance);

    w.create(hInstance);
    w.show();

    Instance::run();
}
