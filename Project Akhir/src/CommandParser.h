#pragma once

#include "Includes.h"

class CommandParser
{
private:
	std::unordered_map<std::string, int> listMaps;
	std::queue<std::string> parsingQueue;

public:
	CommandParser() = default;

	void parse(std::string commands) {
		//std::string temp = "";
		//for (int i = 0; i < commands.length(); i++) {
		//	if (commands[i] == ' ') {
		//		parsingQueue.push(temp);
		//		temp.clear();
		//	}
		//	else {
		//		temp += commands[i];
		//	}
		//}

		//std::string keyword = parsingQueue.front();

		//// listMaps["hello"] = hello;

		//if (listMaps.find(keyword) != listMaps.end()) 
		//{
		//	// listMaps[keyword]();
		//}


	}

};