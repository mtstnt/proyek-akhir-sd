#include "MainMenuState.h"

#include "FileSystem.h"

#include "GameState.h"
#include "CreditState.h"
#include "SettingState.h"


FS::MainMenuState::MainMenuState(GameDataRef data): m_data(data)
{
}

FS::MainMenuState::~MainMenuState()
{
}

void FS::MainMenuState::VInit()
{
	system("cls");
}

void FS::MainMenuState::VUpdate(float dt)
{
	system("cls");
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
	system("cls");
}

void FS::MainMenuState::GameTitle()
{
	std::cout << FileSystem::get().readFile("files/Title.txt", true, false) << std::endl;
}

void FS::MainMenuState::GameMenu()
{
	std::cout << "MAIN MENU " << std::endl;
	std::cout << "1. Play   " << std::endl;
	std::cout << "2. Credits" << std::endl;
	std::cout << "3. Setting" << std::endl;
	std::cout << "0. Quit   " << std::endl;
	char choice; std::cin >> choice;

	switch (choice)
	{
	case '1':
		std::cout << "is Playing" << std::endl;
		m_data->machine.AddState(std::make_unique<GameState>(m_data), false);
		break;
	case '2':
		std::cout << "is Credits" << std::endl;
		m_data->machine.AddState(StateRef(new CreditState(m_data)), false);
		break;
	case '3':
		std::cout << "is Credits" << std::endl;
		m_data->machine.AddState(StateRef(new SettingState(m_data)), false);
		break;
	case '0':
		std::cout << "Press again to exit.." << std::endl;
		this->VExit();
		break;
	default:
		break;
	}
	
}
