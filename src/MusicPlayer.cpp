#include "MusicPlayer.h"

FS::MusicPlayer::MusicPlayer()
{
}

FS::MusicPlayer::~MusicPlayer()
{
}

void FS::MusicPlayer::play()
{
    PlaySound(TEXT("files/Music.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
}

void FS::MusicPlayer::stop()
{
    PlaySound(NULL, NULL, 0);
}
