#pragma once
#include "Includes.h"

#include "GameInfo.h"
#include "Utils.h"
#include "Tools.h"

// Cara kerja class anakan e BaseCommand:
// Setiap class ini menjalankan beberapa fungsi. Misalnya utk display directory dia panggil class ListDirectory, utk pergi pake class GotoDirectory.

// Utk case tools, cuma menjalankan tools yang ada, ke directory yang dikirim via parameter.
// Hasil eksekusinya dimasukin ke dlm string yang direturn via getResponse();

// Commands
class BaseCommand
{
protected:
	std::vector<std::string> params;

	GameInfo& data;

public:

	BaseCommand(GameInfo& data) : data(data) {}
	
	virtual void parse(const std::string& paramString) 
	{
		params = Utils::split(paramString);
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
	std::string response;

public:
	GotoDirectory(GameInfo& data) : BaseCommand(data) {}

	void parse(const std::string& params) override {
		BaseCommand::parse(params);

		if (params.size() <= 1) {
			response = "";
			return;
		}

		if (this->params[1] == "..") {
			if (data.currentNode->getParent() != nullptr) {
				data.currentNode = data.currentNode->getParent();
				data.currentPath.pop();
			}
			else {
				response = "Already at root!";
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
				response = "Cannot find " + this->params[1];
				return;
			}

			data.currentNode = next;
			data.currentPath.push(next->getName());
		}
	}

	std::string getResponse() override {
		return response;
	}
};

class UseTool : public BaseCommand
{
private:
	std::string response;
public:
	UseTool(GameInfo& info) : BaseCommand(info) {}

	void parse(const std::string& paramString) override
	{
		// CommandParams[1] => toolname
		// CommandParams[2] => tooltarget
		// The rest? DISCARD
		BaseCommand::parse(paramString);

		if (params.size() == 1) {
			// List all available tools
			response = "Tools available: \n";
			for (auto& x : data.tools) {
				response += x.first;
			}
			return;
		}

		if (params[1] == "" || params[1] == " ") {
			// List all available tools
			response = "Tools available: \n";
			for (auto& x : data.tools) {
				response += x.first;
			}
			return;
		}
	}

	std::string getResponse() override {
		return response;
	}

};