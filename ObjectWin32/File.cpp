#include "File.h"

File::File():
	fileHandle(NULL)
{
}

File::~File()
{
}

bool File::openReadOnly(const std::string& fileName)
{
	this->fileHandle = CreateFileA(
		fileName.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	bool result = true;

	if (this->fileHandle == INVALID_HANDLE_VALUE) {
		result = false;
	}

	return result;
}

std::string File::read()
{
	return std::string();
}
