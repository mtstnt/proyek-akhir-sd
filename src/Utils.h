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
}