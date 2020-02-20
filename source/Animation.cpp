#include "../include/Animation.h"
#if defined(__WIN32__)
#include <algorithm>
#endif

namespace GGE
{

    Animation::Animation()
    {
    }

    Animation::~Animation()
    {

    }

    void Animation::loadFrames(TextureAtlas *_textureAtlas, float _frameDuration, std::vector<std::string> _framesNames)
    {
        frameDuration = _frameDuration;
        for(std::vector<std::string>::iterator it = _framesNames.begin(); it != _framesNames.end(); ++it) {
            std::string name = *it;
            TextureRegion *textureRegion = _textureAtlas->regions.at(name);
            frames.push_back(textureRegion);
        }

    }

    TextureRegion* Animation::getCurrentTextureRegion(float elapsedTime, AnimationPlayMode playMode)
    {
        unsigned int frameIndex = (int) (elapsedTime / frameDuration);
        switch(playMode)
        {

            case ANIM_NORMAL:

                frameIndex = std::min((int)frames.size() - 1, (int) frameIndex);

            break;
            case ANIM_LOOP:

                frameIndex = frameIndex % frames.size();

            break;
            case ANIM_LOOP_PINGPONG:

                frameIndex = frameIndex % ((frames.size() * 2) - 2);
                if (frameIndex >= frames.size()) frameIndex = frames.size() - 2 - (frameIndex - frames.size());

            break;

        }
        return frames[frameIndex];
    }

}
