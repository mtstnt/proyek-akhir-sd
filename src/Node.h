#pragma once
#include "Includes.h"

class DirectoryTree;

enum class Type {
	Directory,
	File,
	Virus
};

class Node
{
protected:
	Node* parent;
	std::string name;
	int level;

public:
	Node() = default;
	Node(std::string name) : name(name) {}

	virtual Type checkType() = 0;

	std::string getName() {
		return name;
	}

	void setParent(Node* parent) {
		this->parent = parent;
	}

	void setLevel(int level) {
		this->level = level;
	}

	Node* getParent() {
		return this->parent;
	}

	int getLevel() {
		return level;
	}

	template<typename T>
	T as() {
		return dynamic_cast<T>(this);
	}
};

class Directory : public Node
{
private:
	std::vector<Node*> children;
	int isolateDuration = 0;
	DirectoryTree* treeRef = nullptr;

public:
	Directory() = default;
	Directory(std::string name, DirectoryTree* treeRef) 
		: Node(name), treeRef(treeRef) {}

	// Butuh di file lain karena ada circular dependency disini
	void deleteChild(Node* node);

	Type checkType() override {
		return Type::Directory;
	}

	Node* addChild(Node* child) {
		children.push_back(child);
		return children.back();
	}

	void deleteChild(int index) {
		delete children[index];
		children.erase(children.begin() + index);
	}

	std::vector<Node*>& getChildren() {
		return children;
	}

	void shuffleChildren() {
		for (int i = 0; i < children.size(); i++) {
			int num = binaryRandom();
			if (num) {
				int nextRand = rand() % children.size();
				std::swap(children[i], children[nextRand]);
			}
		}
	}

	void setIsolationDuration(int isolation) {
		this->isolateDuration = isolation;
	}

	int getIsolationDuration() { return this->isolateDuration; }

};

class File : public Node
{
private:
	int size;
	std::string extension;

public:
	File() = default;
	File(std::string name, std::string extension = "") : Node(name), extension(extension) {}

	Type checkType() override {
		return Type::File;
	}
};