#pragma once
#include "IState.h"
#include "App.h"

namespace FS
{
	class MainMenuState : public IState
	{
	private:
		GameDataRef m_data;
	public:
		MainMenuState(GameDataRef data);
		~MainMenuState();

		//IState Function
		virtual void VInit();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();

		void GameTitle();
		void GameMenu();
	};
}


