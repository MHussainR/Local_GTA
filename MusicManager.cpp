#include "MusicManager.hpp"

MusicManager::MusicManager(const char *filename)
{
    // Initialize the audio system
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    // Load the music file
    music_ = Mix_LoadMUS(filename);
    if (!music_)
    {
        // Handle error when loading music
    }
}

bool MusicManager::Load(const std::string &filename)
{
    // Load the music file
    music_ = Mix_LoadMUS(filename.c_str());
    return (music_ != nullptr);
}

bool MusicManager::Load()
{
    // Check if the music is loaded
    return (music_ != nullptr);
}

void MusicManager::Play()
{
    // Start playing the music in a loop
    Mix_PlayMusic(music_, -1);
}

void MusicManager::Play(int loop)
{
    // Start playing the music with the specified loop count
    Mix_PlayMusic(music_, loop);
}

void MusicManager::Pause()
{
    // Pause the currently playing music
    Mix_PauseMusic();
}

void MusicManager::Resume()
{
    // Resume the paused music
    Mix_ResumeMusic();
}

void MusicManager::Stop()
{
    // Stop playing the music
    Mix_HaltMusic();
}

bool MusicManager::IsPlaying()
{
    // Check if music is currently playing
    return Mix_PlayingMusic() == 1;
}
