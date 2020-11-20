#pragma once

#include "Includes.h"

// Cara utk setup warna-warna di console

namespace Console {

	HANDLE hConsole;
	bool isInitialized = false;
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

	void setConsoleSize(int width, int height) {
#ifdef _WIN32
		HWND console = GetConsoleWindow();
		RECT ConsoleRect;
		GetWindowRect(console, &ConsoleRect);
		MoveWindow(console, ConsoleRect.left, ConsoleRect.top, width, height, TRUE);
#endif // _WIN32
	}
}