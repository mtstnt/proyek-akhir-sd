#pragma once

#include "Includes.h"
#include "GameInfo.h"
#include "Commands.h"
#include "CommandHistory.h"

class CommandParser
{
private:
	std::unique_ptr<BaseCommand> command;
	CmdH* command_history;

public:
	std::string CurKey;//will

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

		std::string currentKeyword = parsingQueue.front();
		CurKey = parsingQueue.front();
		parsingQueue.pop();

		// Checking
		if (currentKeyword == "ls") {
			command = std::make_unique<ListDirectory>(info);
			command_history->addLog(commands);
			return;
		}
		if (currentKeyword == "cd") {
			command = std::make_unique<GotoDirectory>(info);
			command->parse(commands);
			command_history->addLog(commands);
			return;
		}
		if (currentKeyword == "tools") {
			command = std::make_unique<UseTool>(info);
			command->parse(commands);
			command_history->addLog(commands);
			return;
		}
		if (currentKeyword == "rm") {
			command = std::make_unique<Remove>(info);
			command->parse(commands);
			command_history->addLog(commands);
			return;
		}
		if (currentKeyword == "?" || currentKeyword == "help") {
			command = std::make_unique<Help>(info);
			command->parse(commands);
			command_history->addLog(commands);
			return;
		}
		if (currentKeyword == "color" || currentKeyword == "COLOR" || currentKeyword == "Color") {
			command = std::make_unique<Color>(info);
			command->parse(commands);
			command_history->addLog(commands);
			return;
		}
		if (currentKeyword == "cls" || currentKeyword == "CLS" || currentKeyword == "Cls") {
			command = std::make_unique<CLS>(info);
			command->parse(commands);
			command_history->addLog(commands);
			return;
		}

	}

	std::string response() {
		if (command == nullptr) {
			return "We don't know that command!";
		}
		std::string response = command->getResponse();
		command = nullptr;
		return response;
	}

	void setLogger(CmdH* cmdHistory) {
		this->command_history = cmdHistory;
	}

};