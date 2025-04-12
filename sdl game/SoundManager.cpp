#include "SoundManager.h"
#include <iostream>
#include <map>

Mix_Music* SoundManager::music = nullptr;
std::map<std::string, Mix_Chunk*> SoundManager::effects;

bool SoundManager::Init() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer init error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void SoundManager::Clean() {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    for (auto& effect : effects) {
        Mix_FreeChunk(effect.second);
    }
    effects.clear();

    Mix_CloseAudio();
}

bool SoundManager::LoadMusic(const std::string& fileName) {
    music = Mix_LoadMUS(fileName.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void SoundManager::PlayMusic(int loops) {
    if (music) Mix_PlayMusic(music, loops);
}

void SoundManager::StopMusic() {
    Mix_HaltMusic();
}

bool SoundManager::LoadEffect(const std::string& id, const std::string& fileName) {
    Mix_Chunk* effect = Mix_LoadWAV(fileName.c_str());
    if (!effect) {
        std::cerr << "Failed to load effect " << fileName << ": " << Mix_GetError() << std::endl;
        return false;
    }
    effects[id] = effect;
    return true;
}

void SoundManager::PlayEffect(const std::string& id) {
    if (effects.count(id)) {
        Mix_PlayChannel(-1, effects[id], 0);
    }
}

