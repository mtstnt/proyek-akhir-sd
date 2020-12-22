#include "CreditState.h"

FS::CreditState::CreditState(GameDataRef data): m_data(data)
{
}

FS::CreditState::~CreditState()
{
}

void FS::CreditState::VInit()
{
	system("CLS");
}

void FS::CreditState::VUpdate(float dt)
{
	system("CLS");
	std::cout << "Matthew S		/ C14190085	\n";
	std::cout << "William TM		/ C14190146	\n";
	std::cout << "Vincent D		/ C14190162	\n";

	std::cout << "Back (Press X): " << std::endl;
	char input; std::cin >> input;
	if (input == 'X' || input == 'x')
	{
		VExit();
	}
}

void FS::CreditState::VResume()
{
}

void FS::CreditState::VPause()
{
}

void FS::CreditState::VExit()
{
	m_data->machine.RemoveState();
	system("CLS");
}
