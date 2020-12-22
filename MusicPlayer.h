#pragma once
#include "Includes.h"
#include "LinkedList.h"

namespace FS
{
	class MusicPlayer
	{
	private:
		LinkedList<std::string> list;
		bool isLooping = false;
		bool file_open = false;
		int get = 0;

	public:
		MusicPlayer();
		~MusicPlayer();

		void play();
		void stop();
		void display();
		void ChangeTrack(std::string str);
	};
}


