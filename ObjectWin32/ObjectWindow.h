#pragma once

#include <Windows.h>

class ObjectWindow
{
public:
	HWND getHandle() const;
protected:
	HWND hwnd;
};

