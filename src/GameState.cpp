#include "GameState.h"	

#include "FileSystem.h"

#include "Tools.h"

FS::GameState::GameState(GameDataRef data) : m_data(data) {}

FS::GameState::~GameState() {}

void FS::GameState::VInit()
{
	std::cout << "Starting Game...\n";
	Sleep(300);

	// Setup tree.
	data.tree.setMaxLevel(7);
	data.tree.setMaxElements(8);
	data.tree.setVirusCount(3);
	data.tree.setMinimumVirusLevel(3);
	data.tree.initializeTree();

	// Setup pathnya player. Disimpen di GameInfo
	Node* root = data.tree.getRoot();
	data.currentNode = root;
	data.currentPath.push("root");

	// Setup tools.
	data.tools["detector"] = new Tool_Detector(data);
	//data.tools["isolate"] = new ToolIsolate(data);

   // Bersihin stdin dari enter yang dari cinnya menu.
	getchar();

	data.tree.dfs();
}

void FS::GameState::VUpdate(float dt)
{
	//Console::get().setColor(1);

	// Ask for input
	writePath();
	std::cout << " >";

	// Minta input
	getline(std::cin, input);

	// Biar cepet
	if (input == "quit") {
		VExit();
	}
	else if (input == "dfs") {
		data.tree.dfs();
		std::cout << "\n";
	}

	// Parse input. Semua proses dia inputnya mau ngapain ada di CommandParser.
	parser.parse(data, input);

	// Response dari eksekusi command dari parser dikirimkan ke prompt.
	std::cout << parser.response() << "\n";

	if (data.tree.getVirusesList().size() == 0) {
		std::cout << "SELAMAT! ANDA MENANG!\n";
		VExit();
		return;
	}

	updateVirus();
	updateTools();

	if (is_over) {
		VExit();
		return;
	}
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
		if (v->getParent() == data.tree.getRoot()) {
			std::cout << "ANDA KALAH!\n";
			is_over = true;
			return;
		}

		if (v->getParent()->as<Directory*>()->getChildren().size() <= 1) {
			// Pindahin node ini ke parentnya
			Directory* previous_directory = v->getParent()->as<Directory*>();
			Directory* new_directory = v->getParent()->getParent()->as<Directory*>();

			new_directory->getChildren().push_back(v);
			for (int i = 0; i < previous_directory->getChildren().size(); i++) {
				if (v == previous_directory->getChildren()[i]) {
					previous_directory->getChildren().erase(
						previous_directory->getChildren().begin() + i
					);
					break;
				}
			}
			v->setParent(new_directory);
			// Shuffle biar gk nd bwh terus
			new_directory->shuffleChildren();
		}
		else {
			v->updateVirus();
		}
	}
}
