#pragma once

#include "Includes.h"
#include "Node.h"
#include "FileSystem.h"

class DirectoryTree
{
private:
	Directory* root;
	Node* current;
	int maxLevel;
	int maxElements = 10;

public:
	DirectoryTree(int maxLevel) : maxLevel (maxLevel) {
	
		root = new Directory("root");
	}

	void random() 
	{
		FS::loadRandomFiles();
		Node* temp = root;
		populate(1, root);
	}

	void populate(int level, Node* now) {
		if (level == maxLevel) {
			return;
		}

		if (now == nullptr) {
			return;
		}

		Directory* dir = dynamic_cast<Directory*>(now);
		if (dir == nullptr) {
			return;
		}

		int childCount = rand() % (maxElements - 3) + 3;
		for (int i = 0; i < childCount; i++) {
			if (binaryRandom()) {
				dir->addChild(new Directory(FS::getRandomFoldername()));
			}
			else {
				dir->addChild(new File(FS::getRandomFilename()));
			}

			populate(level + 1, dir->getChildren().at(i));
		}
	}

	void dfs() {
		display(root, 1);

		std::cout << "=========\n";

		std::cout << root->getChildren().size() << "\n";
	}

	void display(Node* now, int level) {

		for (int i = 1; i < level; i++) {
			std::cout << "\t";
		}
		std::cout << now->getName() << std::endl;

		if (now->checkType() != Type::Directory) {
			return;
		}

		Directory* n = (Directory*)now;

		for (int i = 0; i < n->getChildren().size(); i++) 
		{
			display(n->getChildren()[i], level + 1);
		}
	}

};