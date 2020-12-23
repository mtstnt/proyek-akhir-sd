#include "CommandHistory.h"

CmdH::CmdH() {
	head = NULL;
	cur = NULL;
}

void CmdH::addLog(std::string cmd) {
	node* tmp = new node();
	tmp->log = cmd;
	tmp->next = NULL;
	if (head == NULL) {
		head = tmp;
		cur = tmp;
	}
	else {
		cur->next = tmp;
		cur = tmp;
	}
}

void CmdH::DisplayLog() {
	node* c = head;
	std::cout << "Command Log History\n";
	int i = 1;
	while (c != NULL) {
		std::cout << i << ". " <<  c->log << "\n";
		c = c->next;
		i++;
	}
}