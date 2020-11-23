#pragma once

#include <Windows.h>
#include <string>

class File
{
public:
	File();
	~File();

	bool close();
	bool openReadOnly(const std::string& fileName);
	

	std::string read();
	std::string readChars(unsigned int nbChar);
	
	unsigned long getCursorPosition() const;
	void setCursorPosition(unsigned long cursorPosition);
	void moveCursorPosition(long cursorOffset);

	unsigned long getSize() const;
private:
	void checkOpening() const;
	HANDLE fileHandle;
};

