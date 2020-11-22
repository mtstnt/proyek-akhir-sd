#pragma once

#include "Includes.h"

enum class Type {
	Directory,
	File,
	Executable,
	Virus
};

class Node
{
protected:
	Node* parent;
	std::string name;

public:
	Node() = default;
	Node(std::string name) : name(name) {}

	virtual Type checkType() = 0;
	
	const std::string getName() {
		return name;
	}
};

class Directory : public Node
{
private:
	std::vector<Node*> children;

public:
	Directory();
	Directory(std::string name) : Node(name) {}

	Type checkType() override {
		return Type::Directory;
	}

	void addChild(Node* child) {
		children.push_back(child);
	}

	void deleteChild(int index) {
		delete children[index];
		children.erase(children.begin() + index);
	}

	const std::vector<Node*>& getChildren() const {
		return children;
	}

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

class Virus : public Node
{
private:
	int size;

public:
	Virus() = default;
	Virus(std::string name) : Node(name) {}

	Type checkType() override {
		return Type::Virus;
	}
};