#pragma once

#include "ObjectWindow.h"
#include <string>

class Button : public ObjectWindow
{
public:
	Button(ObjectWindow &parent, const std::wstring& text);
	~Button();

	std::wstring getText() const;
};

