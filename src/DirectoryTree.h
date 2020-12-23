#pragma once

#include "Includes.h"
#include "Node.h"
#include "Virus.h"
#include "FileSystem.h"
#include "Utils.h"

class DirectoryTree
{
private:
	Directory* root;
	int maxLevel = 8;
	int maxElements = 5;
	int virusCount = 2;
	int minimumVirusLevel = 2;
	int minimumFolderGuarantee = 5;

	std::vector<virus*> viruses;

	void populate(int level, Node* now) {
		if (level == maxLevel || now == nullptr) {
			return;
		}

		Directory* dir = dynamic_cast<Directory*>(now);
		if (dir == nullptr) {
			return;
		}

		int childCount = rand() % (maxElements)+1;

		// Memastikan ada 1 folder minimum selama level < 3
		bool guaranteeFolder = level <= this->minimumFolderGuarantee ? true : false;

		for (int i = 0; i < childCount; i++) {
			int random = rand() % 100;
			if (random > 75 || guaranteeFolder)
			{
				std::string folderName;
				do {
					folderName = FileSystem::get().getRandomFoldername();
				} while (!Utils::isDistinct(dir, folderName));

				Node* t = dir->addChild(new Directory(folderName, this));

				t->setParent(now);
				t->setLevel(level);

				guaranteeFolder = false;
			}
			else
			{
				std::string fileName;
				do {
					fileName = FileSystem::get().getRandomFilename();
				} while (!Utils::isDistinct(dir, fileName));

				Node* t = dir->addChild(new File(FileSystem::get().getRandomFilename()));

				t->setParent(now);
				t->setLevel(level);
			}

			populate(level + 1, dir->getChildren().at(i));
		}

		dir->shuffleChildren();
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
		root = new Directory("root", this);
	}

	DirectoryTree(int maxLevel) : maxLevel(maxLevel) {
		root = new Directory("root", this);
	}

	~DirectoryTree() {
		std::stack<Node*> dir_stack;
		dir_stack.push(root);
		while (!dir_stack.empty()) {
			Node* current_node = dir_stack.top();
			dir_stack.pop();

			if (current_node->checkType() == Type::Directory) {
				Directory* current_node_as_dir = current_node->as<Directory*>();
				for (int i = 0; i < current_node_as_dir->getChildren().size(); i++) {
					dir_stack.push(current_node_as_dir->getChildren()[i]);
				}
				current_node_as_dir->getChildren().clear();
			}

			delete current_node;
		}
	}

	void setMaxElements(int size) {
		this->maxElements = size;
	}

	void setMaxLevel(int level) {
		this->maxLevel = level;
	}

	void setVirusCount(int c) {
		this->virusCount = c;
	}

	void setMinimumVirusLevel(int n) {
		this->minimumVirusLevel = n;
		this->minimumFolderGuarantee = n;
	}

	void initializeTree()
	{
		FileSystem::get().loadRandomFiles();
		root->setLevel(1);
		populate(1, root);
		initializeViruses(virusCount);
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

	// FUnction untuk insert virus ke tree.
	void initializeViruses(int count) {
		std::stack<Node*> stack;
		stack.push(getRoot());
		Node* prevDir = nullptr;
		while (!stack.empty()) {
			Node* n = stack.top();
			stack.pop();

			if (n->checkType() != Type::Directory) {
				continue;
			}

			Directory* d = n->as<Directory*>();

			if (
					rand() % 100 > 50 &&
					count > 0 && 
					d->getLevel() > this->minimumVirusLevel &&
					prevDir != d
				) {
				// Make new virus
				std::string fileName;
				do {
					fileName = FileSystem::get().getRandomFilename() + "VIRUS";
				} while (!Utils::isDistinct(d, fileName));

				virus* vrs = new virus(fileName, rand());
				// Add ke node
				d->addChild(vrs);

				// Add ke list virus
				viruses.push_back(vrs);

				vrs->setParent(d);
				vrs->setLevel(d->getLevel() + 1);
				count--;

				prevDir = d;
			}

			for (int i = 0; i < d->getChildren().size(); i++) {
				if (d->getChildren()[i]->checkType() == Type::Directory) {
					stack.push(d->getChildren()[i]);
				}
			}


		}
	}

	std::vector<virus*>& getVirusesList() {
		return viruses;
	}

	
};