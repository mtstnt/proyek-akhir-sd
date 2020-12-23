#pragma once
#include "Includes.h"

class node {
public:
	std::string log;
	node* next;
};

class CmdH : public node {
	node* head, * cur;
public:
	CmdH();
	void addLog(std::string cmd); 
	void DisplayLog();
};

