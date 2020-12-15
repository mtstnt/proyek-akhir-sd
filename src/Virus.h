#pragma once
#include"Tools.h"
#include<iostream>

#include "Node.h"

using namespace std;

class virus : public Node
{
protected:
	int id = 0;
	int size;
	tools t;
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
};

//class V1 : protected virus : virus(ID) {
//protected:
//
//public:
//	V1();
//	void moveToFolder();
//	void deleteFile();
//};
//
//class V2 : protected virus {
//protected:
//
//public:
//	V2();
//	void moveToFolder();
//	void deleteFile();
//};
//
//class V3 : protected virus {
//protected:
//
//public:
//	V3();
//	void moveToFolder();
//	void deleteFile();
//};