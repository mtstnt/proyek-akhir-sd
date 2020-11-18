#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <stack>
#include <ctime>
#include <fstream>

#include <SFML/Audio.hpp>

#ifdef _WIN32

#include <Windows.h>

#endif // __WIN32

inline bool binaryRandom() {
	return rand() % 2;
}