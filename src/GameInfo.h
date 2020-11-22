#pragma once

#include "Includes.h"
#include "DirectoryTree.h"

#include "Utils.h"

struct GameInfo
{
	DirectoryTree tree;
	Utils::IterableStack<std::string> currentPath;
	Node* currentNode;
	int health = 100;
};