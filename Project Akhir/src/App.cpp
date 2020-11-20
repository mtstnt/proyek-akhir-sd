#include "App.h"

#include "FileSystem.h"
#include "DirectoryTree.h"

#include "CommandParser.h"

App::App()
{
}

void App::run()
{
	std::string title = FS::readFile("files/Title.txt", false);

	Console::startHandle();
	Console::setColor(2);

	std::cout << title << std::endl;

	/*Console::setColor(9);
	DirectoryTree tree(15);
	tree.random();
	tree.dfs();*/

	std::cout << "Start playing?\n";
	getch();

	std::string input;
	getline(std::cin, input);
}
