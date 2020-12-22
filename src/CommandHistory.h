#pragma once
#include "CommandParser.h"

class node {
public:
	std::string log;
	node* next;
};

class CmdH : public node {
	CommandParser CP;
	node* head, * cur;
public:
	CmdH();
	void addLog(); 
	void DisplayLog();
};

