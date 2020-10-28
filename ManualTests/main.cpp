#include <Windows.h>
#include "MainWindow.h"
#include "Instance.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    Instance::init(hInstance);

    MainWindow w;

    w.create(hInstance);
    w.show();

    Instance::run();

    return 0;
}