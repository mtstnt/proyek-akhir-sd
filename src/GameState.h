#pragma once
#include "IState.h"
#include "App.h"
#include "CommandParser.h"
#include "GameInfo.h"

namespace FS
{
	class GameState : public IState
	{
	private:
		// State management stuff
		GameDataRef m_data;

		// Data yang dikirimkan ke lain-lain utk diproses
		GameInfo data;

		// Object utk parse commands.
		CommandParser parser;

		// Prompt temporary storage
		std::string prompt;
		std::string input;

		// List virus TODO

	public:
		GameState(GameDataRef data);
		~GameState();

		//IState Function
		virtual void VInit();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();

		void writePath() 
		{
			for (int i = 0; i < data.currentPath.size(); i++) {
				std::cout << data.currentPath.get(i);
				if (i != data.currentPath.size() - 1) {
					std::cout << "/";
				}
			}
		}
	};
}
