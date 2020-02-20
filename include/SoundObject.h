#ifndef SOUNDOBJECT_H_INCLUDED
#define SOUNDOBJECT_H_INCLUDED

#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/codec.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>
#include <cstdio>
#include <vector>
#include "ResourcesManager.h"
#if defined(__ANDROID__)
 #include "OS_ANDROID.h"
#elif __APPLE__
 #include "TargetConditionals.h"
 #if TARGET_OS_OSX
  #include "OS_GLFW.h"
 #else
  #include "OS_iOS.h"
 #endif
#else
 #include "OS_GLFW.h"
#endif

#define BUFFER_SIZE     32768       // 32 KB buffers


namespace GGE
{
    class SoundObject
    {
        public:
            SoundObject();
            ~SoundObject();
            void loadSound(bool spatialization, const resourceFile *rf);

            void loadOGG(const resourceFile *rf, std::vector<char> &buffer, ALenum &format, ALsizei &freq);
            inline ALuint getSoundSource() { return soundSource; }

        private:
            ALuint soundBuffer;
            ALuint soundSource;
            ALint state;
            ALenum format;
            ALsizei freq;
            size_t null_read(void *ptr, size_t size, size_t nmemb, void* datasource);
            int null_seek(void* datasource, ogg_int64_t offset, int whence);
            int null_close(void* datasource);
            long null_tell(void* datasource);


    };
}

#endif // SOUNDOBJECT_H_INCLUDED
