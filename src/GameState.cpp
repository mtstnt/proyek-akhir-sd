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
		if (v == nullptr) continue;

		// Ambil parent dari setiap virus yang terdaftar di list
		Directory* vParent = v->getParent()->as<Directory*>();

		// Check apakah ada non-virus dlm dir yang sama
		bool stillNeedToDelete = false;
		for (Node* n : vParent->getChildren()) {
			if (n->checkType() != Type::Virus && n != v) {
				stillNeedToDelete = true;
				break;
			}
		}

		// Apabila semua non virus dlm directory itu sudah habis, 
		//   pindah folder.
		if (!stillNeedToDelete) {
			if (vParent->getParent() != data.tree.getRoot()) {
				vParent->getParent()
					->as<Directory*>()
					->addChild(v);

				for (int q = 0; q < vParent->getChildren().size(); q++) {
					if (v == vParent->getChildren()[q]) {
						vParent->getChildren().erase(vParent->getChildren().begin() + q);
						break;
					}
				}

				v->setParent(vParent->getParent());
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
