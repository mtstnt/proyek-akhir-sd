#include "Includes.h"
#include "App.h"

void setupConsole() {
#ifdef _WIN32

	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 10000, TRUE);

#endif // _WIN32
}

int main() 
{
	srand(time(NULL));

	// Setup console window size, position
	setupConsole();

	App app;
	app.run();
}