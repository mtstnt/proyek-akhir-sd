#include "SettingState.h"

FS::SettingState::SettingState(GameDataRef data): m_data(data)
{
}

FS::SettingState::~SettingState()
{
}

void FS::SettingState::VInit()
{
}

void FS::SettingState::VUpdate(float dt)
{
	if (audio == true)
	{
		std::cout << "Audio ON" << std::endl;
	}
	else
	{
		std::cout << "Audio OFF" << std::endl;
	}

	if (audio == true)
	{
		m_data->musicPlayer.display();
		std::cout << "Change Track: " << std::endl;
		std::cout << "X to Back: " << std::endl;
		std::cout << "OFF to turn off audio: " << std::endl;
		std::string input; std::cin >> input;
		if (input == "X" || input == "x")
		{
			VExit();
		}
		else if (input == "OFF" || input == "off" || input == "Off")
		{
			audio = false;
			m_data->musicPlayer.stop();
		}
		else
		{
			m_data->musicPlayer.ChangeTrack(input);
		}
	}
	else
	{
		std::cout << "X to Back: " << std::endl;
		std::cout << "ON to turn on audio: " << std::endl;
		std::string input; std::cin >> input;
		if (input == "X" || input == "x")
		{
			VExit();
		}
		else if (input == "ON" || input == "on" || input == "On")
		{
			audio = true;
			m_data->musicPlayer.ChangeTrack("0");
			m_data->musicPlayer.play();
		}
	}
}

void FS::SettingState::VResume()
{
}

void FS::SettingState::VPause()
{
}

void FS::SettingState::VExit()
{
	m_data->machine.RemoveState();
}
