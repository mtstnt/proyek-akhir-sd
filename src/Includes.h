#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <ctime>
#include <fstream>
#include <functional>
#include <conio.h>
#include <stack>
#include <assert.h>
#pragma comment(lib, "Winmm.lib")

#ifdef _WIN32

#include <Windows.h>

#endif // __WIN32

inline bool binaryRandom() {
	return rand() % 2;
}