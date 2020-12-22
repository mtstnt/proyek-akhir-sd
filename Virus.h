#pragma once
#include "Node.h"

using namespace std;

class virus : public Node
{
protected:
	int id = 0;
	int size;
	string loc;
	bool turn;

public:
	virus();
	virus(std::string name, int ID) : Node(name) { }

	Type checkType() override {
		return Type::Virus;
	}

	virtual void moveToFolder();
	virtual void deleteFile();
	void updateVirus();
	void changeName();
	void changeFilename();

	int getID() { return id; }
};