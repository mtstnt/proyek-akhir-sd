#include "App.h"

#include "FileSystem.h"
#include "DirectoryTree.h"

#include "CommandParser.h"

// State includes disini
#include "MainMenuState.h"

App::App()
{
	m_data->machine.AddState(std::make_unique<FS::MainMenuState>(m_data));
}

void App::run()
{
	//std::string title = FileSystem::get().readFile("files/Title.txt", false);

	//Console::get().setColor(2);

	//std::cout << title << std::endl;

	//*Console::setColor(9);
	//DirectoryTree tree(15);
	//tree.random();
	//tree.dfs();*/

	//std::cout << "Start playing?\n";
	//getch();

	//std::string input;
	//getline(std::cin, input);

	m_data->musicPlayer.play();

	Console::get().startHandle();

	while (isRunning) 
	{
		m_data->machine.ProcessStateChanges();
	
		if (m_data->machine.StackEmpty()) {
			isRunning = false;
		}
		else {
			m_data->machine.GetActiveState()->VUpdate(0);
		}

	}
}
