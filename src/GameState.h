#pragma once
#include "IState.h"
#include "App.h"
#include "CommandParser.h"
#include "GameInfo.h"
#include "Virus.h"
#include "CommandHistory.h"

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

		// Max turn, apakah game sudah selesai atau belum
		bool is_over = false;
		const int MAX_TURN = 50;

		CmdH command_history;
		int turn = 0;

	public:
		GameState(GameDataRef data);
		~GameState();

		//IState Function
		virtual void VInit();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();

		void writePath();

		void updateTools();
		void updateVirus();

		void verifyCurrentNode();
	};
}
