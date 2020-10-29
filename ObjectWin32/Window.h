#pragma once

#include "ObjectWindow.h"
#include <string>

class Window : public ObjectWindow
{
public:
	explicit Window();
	explicit Window(Window* newParent);
	~Window();
	static LRESULT CALLBACK RouterWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void create(HINSTANCE hInstance);
	void show();

	//size
	unsigned int getWidth() const;
	unsigned int getHeight() const;

private:
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	std::wstring label;
	Window* parent;
};

