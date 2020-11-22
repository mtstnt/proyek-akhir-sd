#pragma once
#include"Tools.h"
#include<iostream>

using namespace std;

class virus {
protected:
	tools t;
	string loc;
	bool turn;
public:
	virus();
	virtual void moveToFolder() = 0;
	virtual void deleteFile() = 0;
	virtual void endTurn() = 0;
};

class V1 : protected virus {
protected:

public:
	V1();
	virtual void moveToFolder();
	virtual void deleteFile();
	virtual void endTurn();
};

class V2 : protected virus {
protected:

public:
	V2();
	virtual void moveToFolder();
	virtual void deleteFile();
	virtual void endTurn();
};

class V3 : protected virus {
protected:

public:
	V3();
	virtual void moveToFolder();
	virtual void deleteFile();
	virtual void endTurn();
};