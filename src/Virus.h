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
	virus(std::string name, int ID) : Node(name), id(ID) { }

	Type checkType() override {
		return Type::Virus;
	}

	virtual void moveToFolder();
	virtual void deleteFile();
	void updateVirus();
	void changeName();

	int getID() { return id; }
};
