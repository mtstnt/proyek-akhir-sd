#pragma once

#include "Includes.h"

namespace Utils 
{
	template <class T>
	class IterableStack : public std::stack<T>
	{
	public:
		const T& get(int i) {
			return this->c[i];
		}
	};

	inline std::vector<std::string> split(const std::string& str)
	{
		std::vector<std::string> splitResults;
		std::string word;
		for (int i = 0; i <= str.length(); i++)
		{
			if (str[i] == ' ' || i == str.length()) {
				splitResults.push_back(word);
				word.clear();
			}
			else {
				word += str[i];
			}
		}
		return splitResults;
	}

	inline bool isDistinct(Directory* dir, std::string name) {
		auto& ref = dir->getChildren();
		for (Node* n : ref) {
			if (n->getName() == name) {
				return false;
			}
		}
		return true;
	}
}