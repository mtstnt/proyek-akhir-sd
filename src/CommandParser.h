#pragma once

#include "Includes.h"

class CommandParser
{
private:
	std::unordered_map<std::string, std::function<void()>> keywords;
	std::queue<std::string> parsingQueue;

public:
	CommandParser() 
	{

	}

	void parse(std::string commands) 
	{
		std::string temp = "";
		for (int i = 0; i <= commands.length(); i++) 
		{
			if (commands[i] == ' ') {
				parsingQueue.push(temp);
				temp.clear();
			}
			else {
				temp += commands[i];
			}
		}

		while (!parsingQueue.empty())
		{
			std::string currentKeyword = parsingQueue.front();

			parsingQueue.pop();

			// Checking
		}

		
	}

	

};