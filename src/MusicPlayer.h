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
		bool is_on = true;
		int get = 0;

	public:
		MusicPlayer();
		~MusicPlayer();

		void play();
		void stop();
		void display();
		void ChangeTrack(std::string str);

		bool get_status() { return is_on; }
		void set_status(bool b) { this->is_on = b; }
	};
}


