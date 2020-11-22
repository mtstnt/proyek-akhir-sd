#include "MainMenuState.h"

#include "FileSystem.h"

#include "GameState.h"


FS::MainMenuState::MainMenuState(GameDataRef data): m_data(data)
{
}

FS::MainMenuState::~MainMenuState()
{
}

void FS::MainMenuState::VInit()
{
}

void FS::MainMenuState::VUpdate(float dt)
{
	this->GameTitle();
	this->GameMenu();
}

void FS::MainMenuState::VResume()
{
}

void FS::MainMenuState::VPause()
{
}

void FS::MainMenuState::VExit()
{
	m_data->machine.RemoveState();
}

void FS::MainMenuState::GameTitle()
{
	//ASCII art
	// Done
	std::cout << FileSystem::get().readFile("files/Title.txt", true, true) << std::endl;
}

void FS::MainMenuState::GameMenu()
{
	std::cout << "MAIN MENU " << std::endl;
	std::cout << "1. Play   " << std::endl;
	std::cout << "2. Credits" << std::endl;
	std::cout << "0. Quit   " << std::endl;
	char choice; std::cin >> choice;

	switch (choice)
	{
	case '1':
		std::cout << "is Playing" << std::endl;
		m_data->machine.AddState(std::make_unique<GameState>(m_data));
		break;
	case '2':
		std::cout << "is Credits" << std::endl;
		break;
	case '0':
		std::cout << "Press again to exit.." << std::endl;
		this->VExit();
		break;
	default:
		break;
	}
	
}
