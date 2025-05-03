#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL_mixer.h>
#include <string>
#include<map>

class SoundManager {

private:
    std::map<std::string, Mix_Music*> musicMap;
    std::map<std::string, Mix_Chunk*> soundMap;
public:
     SoundManager() {}
    ~SoundManager() {}
    static SoundManager& getInstance();
    bool loadMusic(const std::string& id, const std::string& fileName);
    void playMusic(const std::string& id, int loops = -1);
    bool loadSound(const std::string& id, const std::string& fileName);
    void playSound(const std::string& id);
    void stopMusic();
    void clean();

};

#endif
