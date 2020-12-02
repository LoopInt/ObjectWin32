#pragma once

#include "Window.h"
#include <string>

class PushButton : public ObjectWindow
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

private:
	Window& parent;
};

