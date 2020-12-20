#include "CreditState.h"

FS::CreditState::CreditState(GameDataRef data): m_data(data)
{
}

FS::CreditState::~CreditState()
{
}

void FS::CreditState::VInit()
{
}

void FS::CreditState::VUpdate(float dt)
{
	std::cout << "Matthew S		/ C14190085	\n";
	std::cout << "William TM		/ C14190146	\n";
	std::cout << "Vincent D		/ C14190162	\n";

	std::cout << "Thank you for playing Bad Software :)\n";
	std::cout << "Back (Press 0): " << std::endl;
	char input; std::cin >> input;
	if (input == '0')
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
}
