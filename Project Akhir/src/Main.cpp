#include "Includes.h"
#include "App.h"

int main() 
{
	srand(time(NULL));

	// Setup console window size, position
	Console::get().setConsoleSize(1000, 600);

	App app;
	app.run();
}