#pragma once

#include <Windows.h>
#include <string>

class File
{
public:
	File();
	~File();

	bool openReadOnly(const std::string& fileName);
	std::string read();
private:
	HANDLE fileHandle;
};

