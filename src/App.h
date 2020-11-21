#pragma once

#include "Includes.h"
#include "MusicPlayer.h"
#include "StateMachine.h"


struct GameData
{
	FS::StateMachine machine;
	FS::MusicPlayer musicPlayer;
};

typedef std::shared_ptr<GameData> GameDataRef;
class App {

private:
	bool isRunning = true;
	GameDataRef m_data = std::make_shared<GameData>();

public:
	App();

	void run();
	void cleanUp();
};