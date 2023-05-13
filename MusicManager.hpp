#pragma once
#include "game.hpp"
#include <SDL_mixer.h>

class MusicManager
{
private:
    Mix_Music *music_;

public:
    MusicManager() : music_(nullptr) {}
    MusicManager(const char* filename);
    ~MusicManager() { Mix_FreeMusic(music_); }

    bool Load(const std::string &filename);
    bool Load();

    void Play();
    void Play(int loop);

    void Pause();

    void Resume();
    
    void Stop();

    bool IsPlaying();
};