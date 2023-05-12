#include "MusicManager.hpp"

MusicManager::MusicManager(const char *filename)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    // Load the music file.
    music_ = Mix_LoadMUS(filename);
    if (!music_)
    {
        // Handle error.
    }
}

bool MusicManager::Load(const std::string &filename)
{
    music_ = Mix_LoadMUS(filename.c_str());
    return (music_ != nullptr);
}

bool MusicManager::Load()
{
    return (music_ != nullptr);
}

void MusicManager::Play()
{
    Mix_PlayMusic(music_, -1);
}

void MusicManager::Play(int loop)
{
    Mix_PlayMusic(music_, loop);
}

void MusicManager::Pause()
{
    Mix_PauseMusic();
}

void MusicManager::Resume()
{
    Mix_ResumeMusic();
}

void MusicManager::Stop()
{
    Mix_HaltMusic();
}

bool MusicManager::IsPlaying()
{
    return Mix_PlayingMusic() == 1;
}