#include "SoundManager.h"
#include <iostream>

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

bool SoundManager::loadMusic(const std::string& id, const std::string& fileName) {
    Mix_Music* music = Mix_LoadMUS(fileName.c_str());
    if (!music) {
        std::cout << "Failed to load music " << fileName << " Error: " << Mix_GetError() << std::endl;
        return false;
    }
    musicMap[id] = music;
    return true;
}

void SoundManager::playMusic(const std::string& id, int loops) {
    if (musicMap.find(id) != musicMap.end()) {
        Mix_PlayMusic(musicMap[id], loops);
    }
}
bool SoundManager::loadSound(const std::string& id, const std::string& fileName) {
    Mix_Chunk* sound = Mix_LoadWAV(fileName.c_str());
    if (!sound) {
        std::cout << "Failed to load sound " << fileName << " Error: " << Mix_GetError() << std::endl;
        return false;
    }
    soundMap[id] = sound;
    return true;
}
void SoundManager::playSound(const std::string& id) {
    if (soundMap.find(id) != soundMap.end()) {
        Mix_PlayChannel(-1, soundMap[id], 0);
    }
}



void SoundManager::stopMusic() {
    Mix_HaltMusic();
}

void SoundManager::clean() {
    for (auto& m : musicMap) {
        Mix_FreeMusic(m.second);
    }
    musicMap.clear();
    for (auto& s : soundMap) {
    Mix_FreeChunk(s.second);
}
    soundMap.clear();
    Mix_CloseAudio();
}
