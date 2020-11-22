#pragma once
#include "Includes.h"

#include "GameInfo.h"

// Commands
class BaseCommand
{
protected:
	std::vector<std::string> params;

	GameInfo& data;

	void getParams(const std::string& param) 
	{
		std::string singleParam;
		for (int i = 0; i <= param.length(); i++) 
		{
			if (param[i] == ' ' || i == param.length()) {
				params.push_back(singleParam);
				singleParam.clear();
			}
			else {
				singleParam += param[i];
			}
		}
	}

public:

	BaseCommand(GameInfo& data) : data(data) {}
	
	virtual void parse(const std::string& paramString) 
	{
		getParams(paramString);
	}

	virtual std::string getResponse() = 0;
};

class ListDirectory : public BaseCommand
{
public:
	ListDirectory(GameInfo& data) : BaseCommand(data) {}

	std::string getResponse() override 
	{
		Directory* dir = (Directory*)data.currentNode;
		//Console::get().setColor(2);
		std::cout << "Displaying the current directory: " << data.currentNode->getName() << "\n";
		for (int i = 0; i < dir->getChildren().size(); i++)
		{
			std::cout << "----";
			std::cout << dir->getChildren()[i]->getName();
			if (dir->getChildren()[i]->checkType() == Type::Directory) {
				std::cout << "\t<DIR>";
			}

			std::cout << "\n";
		}

		return "";
	}
};

class GotoDirectory : public BaseCommand
{
private:
	std::string responseString;

public:
	GotoDirectory(GameInfo& data) : BaseCommand(data) {}

	void parse(const std::string& params) override {
		BaseCommand::parse(params);

		if (params.size() <= 1) {
			responseString = "";
			return;
		}

		if (this->params[1] == "..") {
			if (data.currentNode->getParent() != nullptr) {
				data.currentNode = data.currentNode->getParent();
				data.currentPath.pop();
			}
			else {
				responseString = "Already at root!";
			}
		}
		else {
			Directory* current = (Directory*)data.currentNode;
			Node* next = nullptr;
			for (int i = 0; i < current->getChildren().size(); i++)
			{
				if (current->getChildren()[i]->getName() == this->params[1])
				{
					next = current->getChildren()[i];
					break;
				}
			}

			if (next == nullptr) {
				responseString = "Cannot find " + this->params[1];
				return;
			}

			data.currentNode = next;
			data.currentPath.push(next->getName());
		}
	}

	std::string getResponse() override {
		return responseString;
	}
};