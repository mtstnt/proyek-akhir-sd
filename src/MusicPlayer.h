#pragma once
#include "Includes.h"


namespace FS
{
	class MusicPlayer
	{
	private:
		std::string filename;
		bool isLooping = false;

	public:
		MusicPlayer();
		~MusicPlayer();

		void play();
		void stop();
	};
}


