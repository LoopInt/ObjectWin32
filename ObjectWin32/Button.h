#pragma once

#include "ObjectWindow.h"
#include <string>

class Button : public ObjectWindow
{
public:
	Button(ObjectWindow &parent, const std::wstring& text);
	~Button();

	void setText(const std::wstring& text);
	std::wstring getText() const;
};

