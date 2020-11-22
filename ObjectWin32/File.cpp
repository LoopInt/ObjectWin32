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
	unsigned long fileSize = this->getSize();

	char* buffer = new char[fileSize+1];
	buffer[fileSize] = '\0';

	ReadFile(
		this->fileHandle,
		buffer,
		fileSize,
		nullptr,
		NULL
	);

	std::string text = buffer;
	delete[] buffer;

	return text;
}

unsigned long File::getSize() const
{
	unsigned long fileSize = GetFileSize(
		this->fileHandle,
		nullptr
	);

	return fileSize;
}
