#ifndef SOUND_MANAGER_H_INCLUDED
#define SOUND_MANAGER_H_INCLUDED

#define OV_EXCLUDE_STATIC_CALLBACKS
#if defined(__WIN32__)
#undef OV_EXCLUDE_STATIC_CALLBACKS
#endif

#include <AL/al.h>
#include <AL/alc.h>
#include "SoundObject.h"

#include <map>
#include <string>
#define BUFFER_SIZE     32768


namespace GGE
{
    class SoundManager
    {
        public:
            static SoundManager *getInstance()
            {
               if (!SoundManager::instance) SoundManager::instance = new SoundManager();
               return SoundManager::instance;
            }
            void destroy();
            void setListenerValues(ALfloat listenerPos[], ALfloat listenerOri[], ALfloat listenerVel[]);
            void addSoundObject(const std::string &name, SoundObject *sound);
            void initSound();
            void finishSound();
            void playSound(const std::string &soundName, float volume, ALfloat sourcePos[], ALfloat sourceOri[], ALfloat sourceVel[], bool loop, bool startAgain);
            void playMusic(const std::string &soundName, float volume, bool loop);
            void stopSound(const std::string &soundName);
            void pauseSound(const std::string &soundName);
            void resumeSound(const std::string &soundName);
            bool isPlaying(const std::string &soundName);

        private:
            ALCdevice* device;
            ALCcontext* context;
            SoundManager();
            static SoundManager *instance;
            std::map<std::string, SoundObject*> soundObjects;

    };
}
#endif // SOUND_MANAGER_H_INCLUDED
