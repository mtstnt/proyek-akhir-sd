#include "CommandHistory.h"

CmdH::CmdH() {
	head = NULL;
	cur = NULL;
}

void CmdH::addLog() {
	node* tmp = new node();
	tmp->log = CP.getCommand();
	tmp->next = NULL;
	if (head == NULL) {
		head = tmp;
		cur = tmp;
	}
	else {
		cur = tmp;
		cur = cur->next;
	}
}

void CmdH::DisplayLog() {
	cur = head;
	std::cout << "Command Log History\n";
	while (cur->next != NULL) {
		std::cout << cur->log << "\n";
		cur = cur->next;
	}
}