#include "App.h"

#include "FileSystem.h"
#include "DirectoryTree.h"

App::App()
{
}

void App::run()
{
	DirectoryTree tree(5);
	tree.random();
	tree.dfs();

	//while (isRunning) {
	//	// Display response

	//	// Ask for input

	//	// Compute command
	//}
}
