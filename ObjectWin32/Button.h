#pragma once

#include "Window.h"
#include <string>

class Button : public ObjectWindow
{
public:
	Button(Window &newParent, const std::wstring& text);
	~Button();

	void setText(const std::wstring& text);
	std::wstring getText() const;

	int getXPos() const;
	int getYPos() const;

private:
	Window& parent;
};

