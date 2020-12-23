#include "App.h"
#include "FileSystem.h"
#include "DirectoryTree.h"
#include "CommandParser.h"
#include "MainMenuState.h"

App::App()
{
	m_data->machine.AddState(std::make_unique<FS::MainMenuState>(m_data));
}

void App::run()
{
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
