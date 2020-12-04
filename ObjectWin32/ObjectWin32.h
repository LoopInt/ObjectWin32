#pragma once

#include <Windows.h>

class ObjectWin32
{
public:
	HWND getHandle() const;
	virtual void command(const unsigned int notif) = 0;

protected:
	HWND hwnd;
};

