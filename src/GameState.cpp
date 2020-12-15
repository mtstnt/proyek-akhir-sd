#include "GameState.h"	

#include "FileSystem.h"

#include "Tools.h"

FS::GameState::GameState(GameDataRef data) : m_data(data) {}

FS::GameState::~GameState()
{
}

void FS::GameState::VInit()
{
	std::cout << "Starting Game...\n";
	Sleep(300);

	// Setup tree.
	data.tree.setMaxLevel(5);
	data.tree.initializeTree();

	// Setup pathnya player. Disimpen di GameInfo
	Node* root = data.tree.getRoot();
	data.currentNode = root;
	data.currentPath.push("root");

	Directory* rootDir = root->as<Directory*>();
	for (auto& a : root->as<Directory*>()->getChildren()) {
		std::cout << a->getName() << std::endl;
	}

	std::cout << "=====================\n";

	// Setup tools.
	data.tools["detector"] = new ToolDetectVirus(data);
	// data.tools["isolate"] = new ToolIsolate(data);

	// Bersihin stdin dari enter yang dari cinnya menu.
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

	// Minta input
	getline(std::cin, input);
	
	if (input == "quit") {
		VExit();
	}

	// Parse input. Semua proses dia inputnya mau ngapain ada di CommandParser.
	parser.parse(data, input);

	// Response dari eksekusi command dari parser dikirimkan ke prompt.
	prompt = parser.response();
}

void FS::GameState::VResume() {}

void FS::GameState::VPause() {}

void FS::GameState::VExit()
{
	m_data->machine.RemoveState();
}