#include "../include/SoundManager.h"
#include <iostream>
#include <fstream>

namespace GGE
{

    SoundManager* SoundManager::instance = 0;

    SoundManager::SoundManager()
    {
    }

    void SoundManager::initSound()
    {
      device = alcOpenDevice( NULL );


      if ( device == NULL )
      {
          fputs( "Couldn't open device", stderr );
      }

      context = alcCreateContext( device, NULL );
      if ( context == NULL )
      {
          fputs( "Error creating context", stderr );
      }

      alcMakeContextCurrent( context );

    }

    void SoundManager::finishSound(){
        alcMakeContextCurrent( NULL );
        alcDestroyContext( context );
        alcCloseDevice( device );
    }

    void SoundManager::playSound(std::string soundName, float volume, ALfloat sourcePos[], ALfloat sourceOri[], ALfloat sourceVel[], bool loop, bool startAgain){

        SoundObject *sound = soundObjects.at(soundName);

        if (sound)
        {
            ALint state;
            alSourcefv(sound->getSoundSource(), AL_POSITION,    sourcePos);
            alSourcefv(sound->getSoundSource(), AL_ORIENTATION,    sourceOri);
            alSourcefv(sound->getSoundSource(), AL_VELOCITY, sourceVel);

            if (loop)
            {
                alSourcei(sound->getSoundSource(), AL_LOOPING, AL_TRUE);
            }

            alSourcef(sound->getSoundSource(), AL_GAIN, volume);

            alGetSourcei(sound->getSoundSource(), AL_SOURCE_STATE, &state);
            if (state != AL_PLAYING || startAgain)
                alSourcePlay(sound->getSoundSource());
        }
    }

    void SoundManager::stopSound(std::string soundName)
    {
        SoundObject *sound = soundObjects.at(soundName);
        if (sound)
        {
            alSourceStop(sound->getSoundSource());
        }
    }

    void SoundManager::pauseSound(std::string soundName)
    {
        SoundObject *sound = soundObjects.at(soundName);
        if (sound)
        {
            alSourcePause(sound->getSoundSource());
        }
    }


    void SoundManager::resumeSound(std::string soundName)
    {
        SoundObject *sound = soundObjects.at(soundName);
        ALint state;

        alGetSourcei(sound->getSoundSource(), AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING)
            alSourcePlay(sound->getSoundSource());

    }

    void SoundManager::playMusic(std::string soundName, float volume, bool loop){

        ALfloat sourcePos[] =  {0.0,0.0,0.0};
        ALfloat sourceOri[] =  {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};
        ALfloat sourceVel[] =  {0.0,0.0,0.0};

        playSound(soundName, volume, sourcePos, sourceOri, sourceVel, loop, false);

    }

    void SoundManager::setListenerValues(ALfloat listenerPos[], ALfloat listenerOri[], ALfloat listenerVel[])
    {
        alListenerfv(AL_POSITION,    listenerPos);
        alListenerfv(AL_VELOCITY,    listenerVel);
        alListenerfv(AL_ORIENTATION, listenerOri);
    }

    bool SoundManager::isPlaying(std::string soundName)
    {
        SoundObject *sound = soundObjects.at(soundName);
        ALint state;
        alGetSourcei(sound->getSoundSource(), AL_SOURCE_STATE, &state);
        return (state == AL_PLAYING);
    }

    void SoundManager::destroy()
    {
        delete instance;
        instance = NULL;
    }

    void SoundManager::addSoundObject(std::string objectName, SoundObject *sound)
    {
        soundObjects.insert(std::make_pair(objectName, sound));
    }

}
