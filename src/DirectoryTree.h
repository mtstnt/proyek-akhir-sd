#pragma once

#include "Includes.h"
#include "Node.h"
#include "FileSystem.h"

class DirectoryTree
{
private:
	Directory* root;
	int maxLevel;
	int maxElements = 3;

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

		int childCount = rand() % (maxElements) + 1;
		for (int i = 0; i < childCount; i++) {
			if (binaryRandom()) {
				Node* t = dir->addChild(new Directory(FileSystem::get().getRandomFoldername()));
				t->setParent(now);
				t->setLevel(level);
			}
			else {
				Node* t = dir->addChild(new File(FileSystem::get().getRandomFilename()));
				t->setParent(now);
				t->setLevel(level);
			}

			populate(level + 1, dir->getChildren().at(i));
		}
	}

	void display(Node* now, int level) {

		if (now == nullptr) {
			return;
		}

		for (int i = 1; i < level; i++) {
			std::cout << "----";
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

public:
	DirectoryTree() 
	{
		maxLevel = 10;
		root = new Directory("root");
	}

	DirectoryTree(int maxLevel) : maxLevel (maxLevel) {
		root = new Directory("root");
	}

	~DirectoryTree() {

	}

	void setMaxLevel(int level) {
		this->maxLevel = level;
	}

	void initializeTree() 
	{
		FileSystem::get().loadRandomFiles();
		root->setLevel(1);
		populate(1, root);
	}

	void dfs(Node* start = nullptr) {
		if (start == nullptr) {
			start = root;
		}

		display(start, start->getLevel());
	}

	// Mungkin 1 1nya yang perlu dipake diluar cuma ini.
	// Bisa dipake utk travel. Harus di cast ke Directory* dulu. 
	// Bisa pake dynamic_cast<Directory*>(node) => Klo null brarti salah. Klo gk brarti bisa dicast.
	Node* getRoot() {
		return root;
	}

	void move(Node* node, Directory* target)
	{
		Directory* parent = node->getParent()->as<Directory*>();
		target->addChild(node);
		
		int idx = -1;
		for (int i = 0; i < parent->getChildren().size(); i++) {
			if (parent->getChildren()[i] == node) {
				idx = i;
				break;
			}
		}

		if (idx != -1) {
			parent->getChildren().erase(parent->getChildren().begin() + idx);
		}

		node->setParent(target);
	}
};