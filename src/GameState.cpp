#include "GameState.h"	
#include "FileSystem.h"
#include "Tools.h"

FS::GameState::GameState(GameDataRef data) : m_data(data) {}
FS::GameState::~GameState() {}

void FS::GameState::VInit()
{
	system("cls");
	std::cout << "Starting Game...\n";

	std::cout << "How to play: \n";
	std::string tutorial_str = FileSystem::get().readFile("files/tutorial.txt", true, false);
	std::cout << tutorial_str << "\n";
	Sleep(500);
	std::cout << "Press any key to continue!\n";
	_getch();

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
	parser.setLogger(&command_history);

	// Setup tools.
	data.tools["detector"] = new Tool_Detector(data);

	// Bersihin stdin dari enter yang dari cinnya menu.
	getchar();
}

void FS::GameState::VUpdate(float dt)
{
	// Win akibat semua virus sudah mati
	if (turn > 0 && data.tree.getVirusesList().size() == 0) {
		std::cout << "YOU WIN!\n";
		_getch();
		VExit();
		return;
	}
	else if (turn == 0 && data.tree.getVirusesList().size() == 0) {
		std::cout << "You're lucky! The viruses decided not to come today!\n";
		std::cout << "Please try playing a new game!\n";
		_getch();
		VExit();
		return;
	}

	// Lose akibat turn habis
	if (turn > MAX_TURN) {
		std::cout << "YOU RAN OUT OF TURNS!\n";
		_getch();
		VExit();
		return;
	}

	// Check apakah kita ada di node yang "illegal" (size childnya 0 atau tinggal virus aja)
	verifyCurrentNode();

	// Tulis path ke current node (kyk di cmd)
	writePath();
	std::cout << " >";

	// Minta input
	getline(std::cin, input);

	// Instant quit
	if (input == "quit" || input == "Quit" || input == "QUIT" || input == "Exit" || input == "EXIT" || input == "exit") {
		is_over = true;
		VExit();
		return;
	}
	else if (input == "history") {
		command_history.DisplayLog();
		std::cout << '\n';
	}
	else if (input == "dfs") {
		data.tree.dfs();
		std::cout << "\n";
	}
	else {
		// Parse input. Semua proses dia inputnya mau ngapain ada di CommandParser.
		parser.parse(data, input);
		
		// Response dari eksekusi command dari parser dikirimkan ke prompt.
		std::cout << parser.response() << "\n";
	}

	updateVirus();

	updateTools();

	if (is_over) {
		VExit();
		return;
	}

	turn++;
	printf("Turn: %d/%d\n", turn, MAX_TURN);
}

void FS::GameState::VResume() {}

void FS::GameState::VPause() {}

void FS::GameState::VExit()
{
	m_data->machine.RemoveState();
	system("cls");
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
			std::cout << "YOU LOST! THE VIRUS HAS REACHED THE ROOT!\n";
			is_over = true;
			return;
		}

		Directory* current_parent = v->getParent()->as<Directory*>();
		bool continue_delete = false;
		for (auto& f : current_parent->getChildren()) {
			if (f->checkType() != Type::Virus) {
				continue_delete = true;
				break;
			}
		}

		if (!continue_delete || v->getParent()->as<Directory*>()->getChildren().size() <= 1) {
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

// Untuk cek apakah node sekarang ada isinya atau gk, Klo gk ada pergi ke parentnya
void FS::GameState::verifyCurrentNode()
{
	bool stay = false;
	for (auto& i : data.currentNode->as<Directory*>()->getChildren())
	{
		if (i->checkType() != Type::Virus) {
			stay = true;
			break;
		}
	}

	if (!stay || data.currentNode->as<Directory*>()->getChildren().size() == 0) {
		// Go back to parent
		data.currentNode = data.currentNode->getParent();
		data.currentPath.pop();
	}
}
