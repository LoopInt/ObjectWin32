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
	unsigned long getSize() const;
private:
	HANDLE fileHandle;
};

