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
		return (T)this;
	}
};

class Directory : public Node
{
private:
	std::vector<Node*> children;

public:
	Directory() = default;
	Directory(std::string name) : Node(name) {}

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