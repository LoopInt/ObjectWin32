#pragma once

#include <Windows.h>

const wchar_t WindowClassName[] = L"WindowClassName";

class Instance
{
public:
	static void init(HINSTANCE newhInstance);
	static void run();
	static HINSTANCE getInstance();
	//static HINSTANCE hInstance;
};

