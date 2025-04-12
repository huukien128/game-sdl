#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL_mixer.h>
#include <string>
#include<map>

class SoundManager {
public:
    static bool Init();
    static void Clean();

    static bool LoadMusic(const std::string& fileName);
    static void PlayMusic(int loops = -1);
    static void StopMusic();

    static bool LoadEffect(const std::string& id, const std::string& fileName);
    static void PlayEffect(const std::string& id);

private:
    static Mix_Music* music;
    static std::map<std::string, Mix_Chunk*> effects;
};

#endif

