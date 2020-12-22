#include "Includes.h"
#include "App.h"

int main() 
{
	srand(time(NULL));

	PlaySound(TEXT("files/Music.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

	// Setup console window size, position
	Console::get().setConsoleSize(1000, 600);

	App app;
	app.run();
}