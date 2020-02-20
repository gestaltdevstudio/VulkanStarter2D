#include "../include/SoundObject.h"
#include <iostream>
#include <fstream>

namespace GGE
{

    size_t null_read(void *ptr, size_t size, size_t nmemb, void* datasource)
    {
     return 0;
    }

    int null_seek(void* datasource, ogg_int64_t offset, int whence)
    {
     return -1;
    }

    int null_close(void* datasource)
    {
     return 0;
    }

    long null_tell(void* datasource)
    {
     return -1;
    }

    static ::ov_callbacks OV_CALLBACKS_PV = {
                  (size_t (*)(void *, size_t, size_t, void *))  null_read,
                  (int (*)(void *, ogg_int64_t, int))           null_seek,
                  (int (*)(void *))                             null_close,
                  (long (*)(void *))                            null_tell
                };

    SoundObject::SoundObject()
    {

    }

    SoundObject::~SoundObject(){
        alSourceStop(soundSource);
        alDeleteSources(1, &soundSource);
        alDeleteBuffers(1, &soundBuffer);
    }

    void SoundObject::loadSound(bool spatialization, const resourceFile *rf)
    {

        alGenBuffers(1, &soundBuffer);
        alGenSources(1, &soundSource);

        alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
        alSource3f(soundSource, AL_POSITION, 0.0f, 0.0f, 0.0f);

        if(alGetError() != AL_NO_ERROR)
            OS::getInstance()->alert("Error while trying to alocate sound memory!\n", rf->fileName);

        if (!spatialization)
        alDistanceModel(AL_NONE);

        std::vector<char> bufferData;
        loadOGG(rf, bufferData, format, freq);

        alBufferData(soundBuffer, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);

        alSourcei(soundSource, AL_BUFFER, soundBuffer);

        if(alGetError() != AL_NO_ERROR)
            OS::getInstance()->alert("Error while trying to load sound file!", rf->fileName);

    }

    void SoundObject::loadOGG(const resourceFile *rf, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
    {
        int endian = 0;
        int bitStream;
        long bytes;
        char array[BUFFER_SIZE];
        FILE *f = NULL;
        std::ofstream of;

        void* bufferChar = rf->content;

        vorbis_info *pInfo;
        OggVorbis_File oggFile;

        ov_open_callbacks(f, &oggFile, static_cast<char*>(bufferChar), rf->size, OV_CALLBACKS_PV);

        pInfo = ov_info(&oggFile, -1);

        if (pInfo->channels == 1)
            format = AL_FORMAT_MONO16;
        else
            format = AL_FORMAT_STEREO16;

        freq = pInfo->rate;

        do
        {

        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);

        if (bytes < 0)
            {
                ov_clear(&oggFile);
                OS::getInstance()->alert("Error decoding sound File ", rf->fileName);
            }

        buffer.insert(buffer.end(), array, array + bytes);
        }
        while (bytes > 0);


        ov_clear(&oggFile);
    }

}
