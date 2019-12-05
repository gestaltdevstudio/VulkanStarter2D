#include "../include/Sprite.h"

#include "../include/GraphicsManager.h"

namespace GGE
{

    Sprite::Sprite(std::string _name)
    {
        playMode = ANIM_NORMAL;
        elapsedTime = 0;
        zOrder = 0;
        name = _name;
    }

    Sprite::~Sprite()
    {
        animations.clear();
    }

    bool Sprite::isCurrentAnimationFinished()
    {
        Animation *animation = getCurrentAnimation();
        int frameNumber = (int)(elapsedTime / animation->getFrameDuration());
        return animation->getNumberOfFrames() - 1 < frameNumber;
    }

    void Sprite::setCurrentAnimationName(std::string _animationName, AnimationPlayMode _playMode)
    {
        currentAnimationName = _animationName;
        playMode = _playMode;
        resetCurrentAnimation();
    }

}
