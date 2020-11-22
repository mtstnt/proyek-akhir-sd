#include "GameState.h"	

#include "FileSystem.h"

// metiu

FS::GameState::GameState(GameDataRef data) : m_data(data) {}

FS::GameState::~GameState()
{
}

void FS::GameState::VInit()
{
	std::cout << "Starting Game...\n";
	Sleep(300);

	data.tree.setMaxLevel(5);

	data.tree.initializeTree();

	Node* root = data.tree.getRoot();
	data.currentNode = root;
	data.currentPath.push("root");

	getchar();
}

void FS::GameState::VUpdate(float dt)
{
	//Console::get().setColor(1);
	// Prompt
	std::cout << prompt << "\n";

	// Ask for input
	writePath();
	std::cout << "$";

	getline(std::cin, input);

	if (input == "quit") {
		VExit();
	}

	parser.parse(data, input);

	prompt = parser.response();
	std::cout << "\n";
}

void FS::GameState::VResume()
{
}

void FS::GameState::VPause()
{

}

void FS::GameState::VExit()
{
	m_data->machine.RemoveState();
}