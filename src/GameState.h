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
		GameDataRef m_data;
		GameInfo data;
		CommandParser parser;

		// Prompt temporary storage
		std::string prompt;
		std::string input;

		// List virus

	public:
		GameState(GameDataRef data);
		~GameState();

		//IState Function
		virtual void VInit();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();

		void traversePath() {
			std::vector<std::string> printablePath;
			printablePath.resize(data.currentPath.size());

			for (int i = 0; i < data.currentPath.size(); i++) {
				std::cout << data.currentPath.get(i);
				if (i != data.currentPath.size() - 1) {
					std::cout << "/";
				}
			}
		}
	};
}
