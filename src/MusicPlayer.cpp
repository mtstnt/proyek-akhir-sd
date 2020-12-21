#include "MusicPlayer.h"

FS::MusicPlayer::MusicPlayer()
{
    std::ifstream infile("files/musiclist.txt");
    if (infile.is_open())
    {
        while (!infile.eof())
        {
            std::string filename;
            infile >> filename;
            list.Append(filename);
        }
        file_open = true;
    }
    else
    {
        file_open = false;
    }
}

FS::MusicPlayer::~MusicPlayer()
{
    //stop();
}

void FS::MusicPlayer::play()
{
    try
    {
        std::string file = list.Get(get);
        std::wstring filename = std::wstring(file.begin(), file.end());
        LPCWSTR str = filename.c_str();
        PlaySound(str, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }
    catch(...)
    {
        std::cout << "Unable to open WAV file!" << std::endl;
        PlaySound(NULL, NULL, 0);
    }
    
}

void FS::MusicPlayer::stop()
{
    PlaySound(NULL, NULL, 0);
}

void FS::MusicPlayer::display()
{
    try
    {
        int size = list.GetSize();
        for (int i = 0; i < size; i++)
        {
            std::string filename = list.Get(i);
            filename = filename.substr(6, filename.length() - 6);
            std::cout << i << ". " << filename << std::endl;
        }
    }
    catch (...)
    {

    }
}

void FS::MusicPlayer::ChangeTrack(std::string str)
{
    int track = std::stoi(str);
    if (track >= 0 && track < list.GetSize())
    {
        get = track;
        stop();
        play();
    }
    else
    {
        std::cout << "Invalid Track" << std::endl;
    }
}
