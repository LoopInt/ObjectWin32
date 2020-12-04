#pragma once

#include "Window.h"
#include "ObjectWin32.h"
#include <string>

class PushButton : public ObjectWin32
{
public:
	PushButton(Window &newParent, const std::wstring& text);
	~PushButton();

	void setText(const std::wstring& text);
	std::wstring getText() const;

	int getXPos() const;
	int getYPos() const;

	void setXPos(int newXPos);
	void setYPos(int newYPos);
	void setPos(int newXPos, int newYPos);

	//signals

	virtual void command(const unsigned int notif);

	void (*isClicked)();

	void command();

private:
	Window& parent;
	static unsigned int idCount;
};

