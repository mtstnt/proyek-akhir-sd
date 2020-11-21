#include "Includes.h"
#include "App.h"
#include "MusicPlayer.h"

void setupConsole() {
#ifdef _WIN32

	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 1000, TRUE);

#endif // _WIN32
}

int main() 
{
	srand(time(NULL));

	// Setup console window size, position
	setupConsole();

	App app;
	app.run();


	return 0;
}