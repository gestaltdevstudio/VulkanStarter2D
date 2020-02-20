#include "../include/Drawable.h"

namespace GGE
{

    Drawable::Drawable()
    {
        visible = false;
        scaleX = scaleY = 1.0f;
        x = y = 0.0f;
        flippedX = flippedY = false;
		rotation = 0;
		color = new Vector4{1.0f,1.0f,1.0f,1.0f};
    }

    Drawable::~Drawable()
    {
        delete color;
    }

    void Drawable::loadRegion(const std::string &regionName, TextureAtlas *_textureAtlas)
    {
        if (_textureAtlas->regions.find(regionName) != _textureAtlas->regions.end())
        {

            textureRegion = static_cast<TextureRegion*>(_textureAtlas->regions.at(regionName));
            textureRegion->textureAtlas = _textureAtlas;

        }

    }

}
