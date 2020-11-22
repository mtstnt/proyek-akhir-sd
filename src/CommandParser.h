#pragma once

#include "Includes.h"
#include "GameInfo.h"
#include "Commands.h"

class CommandParser
{
private:
	std::unique_ptr<BaseCommand> command;

public:
	CommandParser() = default;

	void parse(GameInfo& info, std::string commands)
	{

		std::queue<std::string> parsingQueue;
		std::string temp = "";

		for (int i = 0; i <= commands.length(); i++)
		{
			if (commands[i] == ' ' || i == commands.length()) {
				parsingQueue.push(temp);
				temp.clear();
			}
			else {
				temp += commands[i];
			}
		}

		// Coba param 1 kata aja dlu
		std::string currentKeyword = parsingQueue.front();

		parsingQueue.pop();

		// Checking
		if (currentKeyword == "ls") {
			command = std::make_unique<ListDirectory>(info);
			return;
		}
		if (currentKeyword == "cd") {
			command = std::make_unique<GotoDirectory>(info);
			command->parse(commands);
			return;
		}

		//command = std::make_unique<NotFound>();

	}

	std::string response() {
		if (command == nullptr) {
			return "We don't know that command!";
		}
		return command->getResponse();
	}


};