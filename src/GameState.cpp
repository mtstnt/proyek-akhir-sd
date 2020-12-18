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

	//VIRUS
	vrs = new virus("Corona.exe", 1);
	root->as<Directory*>()->addChild(vrs);
	vrs->setParent(root);
	vrs->moveToFolder();
	//VIRUS

	// Setup tools.
	data.tools["detector"] = new ToolDetectVirus(data);
	// data.tools["isolate"] = new ToolIsolate(data);

	// Bersihin stdin dari enter yang dari cinnya menu.
	getchar();

	/*auto vec = root->as<Directory*>()->getChildren();

	for (int i = 0; i < vec.size(); i++)
	{
		if (vec.at(i)->getName() == "Corona")
		{
			root->as<Directory*>()->deleteChild(i);
			break;
		}
	}*/
	

	//std::cout << "Virus deleted";
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

	try
	{
		vrs->getName();
	}
	catch (...)
	{
		std::cout << "ANDA MENANG" << std::endl;
		VExit();
	}

	if (vrs == nullptr)
	{
		VExit();
	}
	else
	{
		vrs->updateVirus();
	}
	

	
}

void FS::GameState::VResume() {}

void FS::GameState::VPause() {}

void FS::GameState::VExit()
{
	//std::cout << "exiting" << std::endl;
	m_data->machine.RemoveState();
}