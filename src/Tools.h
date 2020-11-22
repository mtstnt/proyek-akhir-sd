#pragma once
#include<iostream>

using namespace std;

class tools {
protected:
	string loc;
	bool turn;
public:
	tools();
	void input(string x);
	void T1();
	void T2();
	void T3();
	bool getTurn();
};