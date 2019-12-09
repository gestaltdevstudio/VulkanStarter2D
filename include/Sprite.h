#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

#include "Drawable.h"
#include "Entity.h"
#include "Animation.h"
#include "GraphicElement.h"

namespace GGE
{

    class Sprite : public Drawable
    {
        public:
            Sprite(std::string _name);
            virtual ~Sprite();
            void setCurrentAnimationName(std::string _animationName, AnimationPlayMode _playMode);
            inline std::string getCurrentAnimationName() { return currentAnimationName; }
            inline Animation* getCurrentAnimation() { return animations.at(currentAnimationName); };
            inline void addAnimation(std::string animationName, Animation *animation) { animations.insert(std::make_pair(animationName, animation)); }
            inline AnimationPlayMode getAnimationPlayMode() { return playMode; }
            inline void setEntity(Entity *_entity) { entity = _entity; }
            inline Entity* getEntity() { return entity; }
            bool isCurrentAnimationFinished();
            inline void updateCurrentAnimation(float deltaTime) { elapsedTime += deltaTime; }
            inline void resetCurrentAnimation() { elapsedTime = 0; }
            inline float getElapsedTime() { return elapsedTime; }
            inline void setZOrder(int _zOrder) { zOrder = _zOrder;}
            inline int getZOrder() { return zOrder; }
            inline std::string getName() { return name; };


        protected:
            Entity *entity;
            std::map<std::string, Animation*> animations;
            std::string currentAnimationName;
            AnimationPlayMode playMode;
            float elapsedTime;
            std::string name;

    };

}

#endif // SPRITE_H_INCLUDED
