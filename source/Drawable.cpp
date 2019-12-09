#include "../include/Drawable.h"

namespace GGE
{

    Drawable::Drawable()
    {
        visible = false;
        scaleX = scaleY = 1.0f;
        x = y = 0.0f;
//        uvbo = 0;
        flippedX = flippedY = false;
		rotation = 0;
		color = new Vector4{1.0f,1.0f,1.0f,1.0f};
    }

    Drawable::~Drawable()
    {
//        if (uvbo)
//			glDeleteBuffers(1, &uvbo);
    }

    void Drawable::loadRegion(std::string regionName, TextureAtlas *_textureAtlas)
    {
        if (_textureAtlas->regions.find(regionName) != _textureAtlas->regions.end())
        {

            textureRegion = static_cast<TextureRegion*>(_textureAtlas->regions.at(regionName));
            textureRegion->textureAtlas = _textureAtlas;

//            if (uvbo)
//                glDeleteBuffers(1, &uvbo);
//
//            glGenBuffers(1, &uvbo);

//            vertices[0].pos = {-atlasRegion->width/2, -atlasRegion->height/2};
//            vertices[0].texCoord = {(float) (atlasRegion->x + atlasRegion->width) / textureAtlas->width,  1.0f - ((float) atlasRegion->y / textureAtlas->height)};
//
//            vertices[1].pos = {-atlasRegion->width/2, atlasRegion->height/2};
//            vertices[1].texCoord = {(float) (atlasRegion->x + atlasRegion->width) / textureAtlas->width,  1.0f - (float) (atlasRegion->y + atlasRegion->height) / textureAtlas->height};
//
//            vertices[2].pos = {atlasRegion->width/2, atlasRegion->height/2};
//            vertices[2].texCoord = {(float) atlasRegion->x / textureAtlas->width,                         1.0f - (float) (atlasRegion->y + atlasRegion->height) / textureAtlas->height};
//
//            vertices[3].pos = {atlasRegion->width/2, -atlasRegion->height/2};
//            vertices[4].texCoord = {(float) atlasRegion->x / textureAtlas->width,                         1.0f - ((float) atlasRegion->y / textureAtlas->height)};

//            float uv[] = {
//                        (float) (atlasRegion->x + atlasRegion->width) / textureAtlas->width,  1.0f - ((float) atlasRegion->y / textureAtlas->height),
//                        (float) (atlasRegion->x + atlasRegion->width) / textureAtlas->width,  1.0f - (float) (atlasRegion->y + atlasRegion->height) / textureAtlas->height,
//                        (float) atlasRegion->x / textureAtlas->width,                         1.0f - (float) (atlasRegion->y + atlasRegion->height) / textureAtlas->height,
//                        (float) atlasRegion->x / textureAtlas->width,                         1.0f - ((float) atlasRegion->y / textureAtlas->height)
//                    };

//            glBindBuffer(GL_ARRAY_BUFFER, uvbo);
//            glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
        }

    }

}
