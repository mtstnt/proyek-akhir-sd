#pragma once

#include "Includes.h"

// Class utk ngatur warna console, ukuran console, posisi cursor, dll.
// Ditambahi nanti ae.
class Console 
{
private:
	HANDLE hConsole;
	bool isInitialized = false;

	static Console* instance;

	Console() = default;

public:

	static Console& get() 
	{
		if (instance == nullptr) {
			instance = new Console();
		}

		return *instance;
	}

	Console& operator=(Console& ref) {
		return *instance;
	}

	void startHandle()
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		isInitialized = true;
	}

	void setColor(int colorIndex)
	{
		if (!isInitialized) {
			std::cout << "Uninitialized handle!\n";
			return;
		}

		SetConsoleTextAttribute(hConsole, colorIndex);
	}

	void setConsoleSize(int width, int height) 
	{
#ifdef _WIN32
		HWND console = GetConsoleWindow();
		RECT ConsoleRect;
		GetWindowRect(console, &ConsoleRect);
		MoveWindow(console, ConsoleRect.left, ConsoleRect.top, width, height, TRUE);
#endif // _WIN32
	}
};

