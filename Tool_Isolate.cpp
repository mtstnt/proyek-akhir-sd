#include "Tool_Isolate.h"

Tool_Isolate::Tool_Isolate(GameInfo & info, const std::string & nodeName)
	: BaseTool(info), parameter(nodeName) {}

bool Tool_Isolate::evaluateConditions()
{
	return BaseTool::evaluateConditions();
}

void Tool_Isolate::doAction()
{
	// Cari node sbg child dri node ini
	Directory* dir = info.currentNode->as<Directory*>();
	Node* nodeToIsolate = nullptr;
	for (auto& node : dir->getChildren()) {
		if (node->getName() == this->parameter) {
			nodeToIsolate = node;
			break;
		}
	}

	if (nodeToIsolate->checkType() != Type::Directory) {
		response = "Error: Cannot isolate a non-directory\n";
		return;
	}

	// Isolate node tsb
	Directory* dirToIsolate = nodeToIsolate->as<Directory*>();

	if (int h = dirToIsolate->getIsolationDuration() > 0) {
		response = "Error: Directory is already isolated for " + std::to_string(h) + "\n";
		return;
	}
	dirToIsolate->setIsolationDuration(this->isolationDuration);
	response = "Directory " + dirToIsolate->getName() + " has been isolated for " + std::to_string(this->isolationDuration) + ".\n";
}
