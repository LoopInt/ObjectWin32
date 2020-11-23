#include "File.h"

File::File():
	fileHandle(NULL)
{
}

File::~File()
{
}

bool File::close()
{
	return CloseHandle(this->fileHandle);
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
	this->checkOpening();

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

std::string File::readChars(unsigned int nbChar)
{
	this->checkOpening();

	char* buffer = new char[nbChar + 1];
	buffer[nbChar] = '\0';

	ReadFile(
		this->fileHandle,
		buffer,
		nbChar,
		nullptr,
		NULL
	);

	std::string text = buffer;
	delete[] buffer;

	return text;
}

unsigned long File::getCursorPosition() const
{
	this->checkOpening();

	unsigned long cursorPosition = SetFilePointer(
		this->fileHandle,
		0,
		NULL,
		FILE_CURRENT
	);

	if (cursorPosition == INVALID_SET_FILE_POINTER) {
		throw std::string("Read cursor position failed.");
	}

	return cursorPosition;
}

void File::setCursorPosition(unsigned long cursorPosition)
{
	this->checkOpening();

	cursorPosition = SetFilePointer(
		this->fileHandle,
		cursorPosition,
		NULL,
		FILE_BEGIN
	);

	if (cursorPosition == INVALID_SET_FILE_POINTER) {
		throw std::string("Read cursor position failed.");
	}
}

void File::moveCursorPosition(long cursorOffset)
{
	this->checkOpening();

	unsigned long cursorPosition = SetFilePointer(
		this->fileHandle,
		cursorOffset,
		NULL,
		FILE_CURRENT
	);

	if (cursorPosition == INVALID_SET_FILE_POINTER) {
		throw std::string("Read cursor position failed.");
	}
}

unsigned long File::getSize() const
{
	unsigned long fileSize = GetFileSize(
		this->fileHandle,
		nullptr
	);

	return fileSize;
}

void File::checkOpening() const
{
	if (this->fileHandle == nullptr) {
		throw std::string("File isn't open.");
	}
}
