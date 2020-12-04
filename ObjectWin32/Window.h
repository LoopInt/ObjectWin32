#pragma once

#include "ObjectWin32.h"
#include <string>
#include <map>

class Window : public ObjectWin32
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
	void maximize();
	bool isMinimized() const;
	bool isMaximized() const;

	//size
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	unsigned int getClientWidth() const;
	unsigned int getClientHeight() const;
	void setWidth(unsigned int newWidth);
	void setHeight(unsigned int newHeight);
	void setSize(const unsigned int newWidth, const unsigned int newHeight);
	void setClientWidth(unsigned int newWidth);
	void setClientHeight(unsigned int newHeight);
	void setClientSize(const unsigned int newWidth, const unsigned int newHeight);
	//position
	unsigned int getXPosition() const;
	unsigned int getYPosition() const;
	int getClientXPosition() const;
	int getClientYPosition() const;
	void setXPosition(const unsigned int newPosX);
	void setYPosition(const unsigned int newPosY);
	void setPosition(const unsigned int newPosX, const unsigned int newPosY);
	void setClientXPosition(const int newPosX);
	void setClientYPosition(const int newPosY);
	void setClientPosition(const int newPosX, const int newPosY);
	//maximize button
	void disableMaximizeButton();
	void enableMaximizeButton();
	//minimize button
	void disableMinimizeButton();
	void enableMinimizeButton();

	void addChildrenWidget(const unsigned int id, ObjectWin32* newChild);

	virtual void command(const unsigned int notif);

private:
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	std::wstring label;
	Window* parent;

	int generateWindowStyle() const;
	void updateStyle();

	bool minimizeButton;
	bool maximizeButton;

	std::map<unsigned int, ObjectWin32*> childs;
};

