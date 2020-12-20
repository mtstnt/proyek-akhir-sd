#pragma once

#include "Tools.h"

class Tool_Detector : public BaseTool
{
protected:
	const char* uniqueName = "detector";

public:
	Tool_Detector(GameInfo& info) : BaseTool(info) {
		this->MAX_COOLDOWN = 3;
		this->cooldown = 0;
	}

	std::string getCurrentPath(Node* n) {
		Node* t = n;
		std::stack<std::string> st;
		while (t != info.tree.getRoot()) {
			st.push(t->getName());
			t = t->getParent();
		}

		std::string result = "";
		while (!st.empty()) {
			result += st.top();
			st.pop();

			if (!st.empty()) {
				result += "/";
			}
		}

		return result;
	}

	void doAction() override
	{
		// DFS through all node in Tree
		std::stack<Node*> nd;
		nd.push(info.tree.getRoot());
		while (!nd.empty()) {
			Node* n = nd.top();
			nd.pop();
			if (n->checkType() != Type::Directory) {
				if (n->checkType() == Type::Virus) {
					this->response = "Found a virus! Location: " + getCurrentPath(n) + "\n";
					this->cooldown = MAX_COOLDOWN;
					return;
				}
				continue;
			}
			
			Directory* dir = n->as<Directory*>();

			for (int i = 0; i < dir->getChildren().size(); i++) {
				nd.push(dir->getChildren()[i]);
			}
		}

		this->response = "No virus found! You are clear.. Or are they hiding?\n";
		this->cooldown = MAX_COOLDOWN;
		std::cout << this->cooldown;
	}
};
