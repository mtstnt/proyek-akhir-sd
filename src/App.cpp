#include "App.h"
#include "MainMenuState.h"

App::App()
{
	//HELLO WORLD
}

void App::run()
{	
	m_data->musicPlayer.play();
	//MAIN GAME LOOP
	m_data->machine.AddState(FS::StateRef(new FS::MainMenuState(this->m_data)), true);
	while (isRunning) 
	{
		m_data->machine.ProcessStateChanges();
		if (m_data->machine.StackEmpty())
		{
			isRunning = false;
		}
		else
		{
			m_data->machine.GetActiveState()->VUpdate(1);
			//Pause a bit and then clear screen, you may wish to not CLS, in that case contact me :)
			char ch = _getch();
			system("CLS");
		}
		
	}
	this->cleanUp();
}

void App::cleanUp()
{
	m_data->musicPlayer.stop();
}
