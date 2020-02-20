#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include "TextureAtlas.h"
#include "GraphicElement.h"

namespace GGE
{

    class Drawable : public GraphicElement
    {

        public:
            Drawable();
            virtual ~Drawable();
            void loadRegion(const std::string &regionName, TextureAtlas *_textureAtlas);

            inline float getX() { return x; };
            inline float getY() { return y; };
            inline float getScaleX() { return scaleX; };
            inline float getScaleY() { return scaleY; };

            inline TextureRegion* getTextureRegion() { return textureRegion; }
            inline bool isVisible() { return visible; }

            inline void setX(float _x) { x = _x; };
            inline void setY(float _y) { y = _y; };
            inline void setScaleX(float _scaleX) { scaleX = _scaleX; };
            inline void setScaleY(float _scaleY) { scaleY = _scaleY; };

            inline void setIsVisible(bool _visible) { visible = _visible; }

            inline void setRotation(float r) { rotation = r;}
            inline float getRotation() { return rotation; }
            inline void setFlippedX(bool _flippedX) { flippedX = _flippedX; }
            inline bool isFlippedX() { return flippedX; }
            inline void setFlippedY(bool _flippedY) { flippedY = _flippedY; }
            inline bool isFlippedY() { return flippedY; }
            inline Vector4* getColor() { return color; }


        protected:
            float x;
            float y;
            float scaleX;
            float scaleY;
            float rotation;

            TextureRegion *textureRegion;
            bool visible;
            bool flippedX;
            bool flippedY;

            Vector4 *color;

    };
}

#endif // DRAWABLE_H_INCLUDED
