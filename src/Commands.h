#pragma once
#include "Includes.h"

#include "GameInfo.h"
#include "Utils.h"
#include "Tools.h"
#include "Tool_Detector.h"

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
	std::string response;

public:

	BaseCommand(GameInfo& data) : data(data) {}
	
	virtual void parse(const std::string& paramString) 
	{
		params = Utils::split(paramString);
	}

	virtual std::string getResponse() {
		return this->response;
	}
};

class ListDirectory : public BaseCommand
{
public:
	ListDirectory(GameInfo& data) : BaseCommand(data) {}

	std::string getResponse() override 
	{
		if (data.currentNode->checkType() != Type::Directory) {
			data.currentNode = data.currentNode->getParent();
			return "Cannot ls in non-directory!\n";
		}

		Directory* dir = data.currentNode->as<Directory*>();

		if (dir == nullptr) {
			data.currentNode = data.currentNode->getParent();
			return "Not a directory!\n";
		}

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
public:
	GotoDirectory(GameInfo& data) : BaseCommand(data) {}

	void parse(const std::string& params) override {
		BaseCommand::parse(params);

		if (this->params.size() <= 1) {
			response = "No path specified.";
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
			Directory* current = data.currentNode->as<Directory*>();
			Node* next = nullptr;
			for (int i = 0; i < current->getChildren().size(); i++)
			{
				if (current->getChildren()[i]->getName() == this->params[1])
				{
					next = current->getChildren()[i];
					break;
				}
			}

			if (next == nullptr) 
			{
				response = "Cannot find " + this->params[1];
				return;
			}

			if (next->checkType() == Type::File || next->checkType() == Type::Virus) {
				response = "Cannot cd into a file!\n";
				return;
			}

			bool stay = false;
			for (auto& i : next->as<Directory*>()->getChildren())
			{
				if (i->checkType() != Type::Virus) {
					stay = true;
					break;
				}
			}

			if (stay) {
				data.currentNode = next;
				data.currentPath.push(next->getName());
			}
			else {
				std::cout << "Cannot enter a deletable directory!\n";
			}
		}
	}
};

class UseTool : public BaseCommand
{
public:
	UseTool(GameInfo& info) : BaseCommand(info) {}

	void parse(const std::string& paramString) override
	{
		// CommandParams[1] => toolname
		// CommandParams[2] => tooltarget
		// The rest? DISCARD
		BaseCommand::parse(paramString);

		if (params.size() == 1 || params[1] == "" || params[1] == " ") {
			// List all available tools
			response = "Tools available: \n";

			for (auto& x : data.tools) {
				response += x.first + "\n";
				response += std::to_string(x.second->getCooldown()) + " turns.";
			}
			
			return;
		}

		if (params[1] == "detector") {
			BaseTool* detector = data.tools["detector"];
			if (detector->evaluateConditions()) {
				detector->doAction();
				response = detector->getResponse();
			}
			else {
				response = "Tool is unavailable for use!\n";
			}
			return;
		}
	}
};

class Remove : public BaseCommand
{
public:
	Remove(GameInfo& data) : BaseCommand(data) {}

	void parse(const std::string& params) override {
		BaseCommand::parse(params);

		if (this->params.size() <= 1) {
			response = "";
			return;
		}
		else
		{
			int deleted_node_id = -1;
			Node* node = data.currentNode;
			auto& children = node->as<Directory*>()->getChildren();
			for (int i = 0; i < children.size(); i++)
			{
				if (children.at(i)->getName() == this->params[1])
				{
					deleted_node_id = i;

					if (children.at(deleted_node_id)->checkType() == Type::Directory) {
						response = "Cannot delete a directory!\n";
						return;
					}

					node->as<Directory*>()
						->deleteChild(children.at(deleted_node_id));

					response = "File deleted!\n";
					break;
				}
			}

			if (deleted_node_id == -1) {
				response = "File not found!\n";
				return;
			}
		}
	}
};

class Help : public BaseCommand
{
public:
	Help(GameInfo& data) : BaseCommand(data) {}

	void parse(const std::string& params) override {
		BaseCommand::parse(params);

		response = "List of commands: \n\tcd [DIR]\n\tls\n\ttools [TOOLS]\n\trm [FILE]";
	}
};

class Color : public BaseCommand
{
private:
	std::string response;

public:
	Color(GameInfo& data) : BaseCommand(data) {}

	void parse(const std::string& params) override {
		BaseCommand::parse(params);

		if (params == "color" || params == "COLOR" || params == "Color")
		{
			system("color 07");
		}
		else
		{
			const char* cmd = params.c_str();
			system(cmd);
		}

		response = "";
	}

	std::string getResponse() override {
		return response;
	}
};

class CLS : public BaseCommand
{
public:
	CLS(GameInfo& data) : BaseCommand(data) {}

	void parse(const std::string& params) override {
		BaseCommand::parse(params);

		system("cls");
		response = "";
	}
};