#ifndef TEXTUREATLAS_H_INCLUDED
#define TEXTUREATLAS_H_INCLUDED

#include "Texture.h"
#include "ResourcesManager.h"
#include <map>
#include "GraphicsUtils.h"

namespace GGE
{

    struct TextureRegion;

    class TextureAtlas
    {
        public:
            TextureAtlas();
            ~TextureAtlas();
            char* imageName;
            char* format;
            char* filter1;
            char* filter2;
            std::map<std::string, TextureRegion*> regions;
            int width;
            int height;

            void* loadTextureAtlas(const resourceFile *atlasConf, const resourceFile *atlasImage);

            Texture    *texture;
    };

    struct TextureRegion
    {
        int index;
		int x;
		int y;
		int width;
		int height;
		TextureAtlas *textureAtlas;
    };


}

#endif // TEXTUREATLAS_H_INCLUDED
