#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <vector>
#include <string>
#include "TextureAtlas.h"
#include "Drawable.h"

namespace GGE
{

    class Animation
    {

        public:
            Animation();
            ~Animation();
            void loadFrames(TextureAtlas *_textureAtlas, float _frameDuration, std::vector<std::string> _framesNames);
            TextureRegion* getCurrentTextureRegion(float elapsedTime, AnimationPlayMode playMode);
            inline float getFrameDuration() { return frameDuration; }
            inline int getNumberOfFrames() { return frames.size(); }

        protected:
            float frameDuration;
            std::vector<TextureRegion*> frames;

    };


}

#endif // ANIMATION_H_INCLUDED
