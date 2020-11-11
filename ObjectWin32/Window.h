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
	//visivbility
	void show();
	void minimize();

	//size
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	//position
	unsigned int getXPosition() const;
	unsigned int getYPosition() const;
	//maximize button
	void disableMaximizeButton();
	void enableMaximizeButton();
	//minimize button
	void disableMinimizeButton();
	void enableMinimizeButton();

private:
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	std::wstring label;
	Window* parent;

	int generateWindowStyle() const;
	void updateStyle();

	bool minimizeButton;
	bool maximizeButton;
};

