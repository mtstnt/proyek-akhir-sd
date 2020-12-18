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
	data.tree.setMaxElements(10);
	data.tree.setVirusCount(2);
	data.tree.initializeTree();

	// Setup pathnya player. Disimpen di GameInfo
	Node* root = data.tree.getRoot();
	data.currentNode = root;
	data.currentPath.push("root");

	// Setup tools.
	data.tools["detector"] = new Tool_Detector(data);
	// data.tools["isolate"] = new ToolIsolate(data);

	// Bersihin stdin dari enter yang dari cinnya menu.
	getchar();
}

void FS::GameState::VUpdate(float dt)
{
	//Console::get().setColor(1);
	// Prompt
	std::cout << prompt << "\n";

	if (data.tree.getVirusesList().size() == 0) {
		std::cout << "SELAMAT! ANDA MENANG!\n";
		VExit();
	}

	// Ask for input
	writePath();
	std::cout << "$";

	// Minta input
	getline(std::cin, input);

	// Biar cepet
	if (input == "quit") {
		VExit();
	}

	// Parse input. Semua proses dia inputnya mau ngapain ada di CommandParser.
	parser.parse(data, input);

	// Response dari eksekusi command dari parser dikirimkan ke prompt.
	prompt = parser.response();

	updateVirus();
	updateTools();
}

void FS::GameState::VResume() {}

void FS::GameState::VPause() {}

void FS::GameState::VExit()
{
	m_data->machine.RemoveState();
}

void FS::GameState::writePath()
{
	for (int i = 0; i < data.currentPath.size(); i++) {
		std::cout << data.currentPath.get(i);
		if (i != data.currentPath.size() - 1) {
			std::cout << "/";
		}
	}
}

void FS::GameState::updateTools()
{
	auto& ref = data.tools;
	for (std::pair<std::string, BaseTool*> b : ref) {
		if (b.second->getCooldown() > 0) {
			b.second->decrementCooldown();
		}
	}
}

void FS::GameState::updateVirus()
{
	auto& ref = data.tree.getVirusesList();
	for (virus* v : ref) {
		Directory* vParent = v->getParent()->as<Directory*>();
		if (vParent->getChildren().size() == 1) {
			if (vParent->getParent() != data.tree.getRoot()) {
				vParent->deleteChild(v);
				vParent->getParent()
					->as<Directory*>()
					->addChild(v);
			}
			else {
				std::cout << "ANDA KALAH!\n";
				VExit();
			}
		}
		else {
			v->updateVirus();
		}
	}
}
