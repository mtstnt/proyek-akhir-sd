#pragma once

#include "Includes.h"
#include "DirectoryTree.h"

#include "Utils.h"

class BaseTool;

struct GameInfo
{
	DirectoryTree tree;
	Utils::IterableStack<std::string> currentPath;
	Node* currentNode;
	int health = 100;

	std::unordered_map<std::string, BaseTool*> tools;
};