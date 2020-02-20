#include "../include/TextureAtlas.h"

#include "../include/GraphicsManager.h"
#include <string.h>

namespace GGE
{

    void* TextureAtlas::loadTextureAtlas(const resourceFile *atlasConf, const resourceFile *atlasImage)
    {

        char * file;
        file = strtok( static_cast<char*>(atlasConf->content),"\r\n");

        char lineHeader[128];

        do
        {
            sscanf(file, "%s", lineHeader);

            if (strcmp( lineHeader, "format:" ) == 0 )
            {
                format = (char*) calloc(24, sizeof(char));
                sscanf(file, "format: %[^\t\n]", format);

            }
            else if (strcmp( lineHeader, "filter:" ) == 0 )
            {
                filter1 = (char*) calloc(24, sizeof(char));
                filter2 = (char*) calloc(24, sizeof(char));
                sscanf(file, "filter: %[^,],%[^\t\n]", filter1, filter2);

            }
            else if (strcmp( lineHeader, "repeat:" ) == 0 )
            {
                ///TODO
            }
            else if ( strcmp( lineHeader, "size:" ) == 0 )
            {
                sscanf(file, "size: %d,%d", &width, &height);
            }
            else if ( strcmp( lineHeader, "%[^:]" ) != 0 )
            {
                imageName = (char*) calloc(128, sizeof(char));
                sscanf(file, "%s", imageName);

            }

            file = strtok ( NULL,"\r\n");

        }while (strcmp( lineHeader, "repeat:" ) != 0);


        TextureRegion *region = NULL;
        char* name;
        while( file != NULL)
        {
            sscanf(file, "%s", lineHeader);

            if (strstr(lineHeader, ":") == NULL)
            {
                if (region)
                {
                    regions.insert(std::make_pair(name, region));
                    free(name);
                }
                name = (char*) calloc(128, sizeof(char));
                region = new TextureRegion();
                sscanf(file, "%s", name);
            }
            if (strncmp(lineHeader, "xy:", strlen("xy:")) == 0)
            {
                sscanf(file, "  xy: %d, %d", &region->x, &region->y);
            }
            if (strncmp(lineHeader, "size:", strlen("size:")) == 0)
            {
                sscanf(file, "  size: %d, %d", &region->width, &region->height);
            }

            region->textureAtlas = this;

            file = strtok ( NULL,"\r\n");

        }

        if (region)
        {
            regions.insert(std::make_pair(name, region));
            if (name)
                free(name);
        }

        texture = GraphicsManager::getInstance()->getRenderer()->createTextureImage(atlasImage);

        return NULL;
    }

    TextureAtlas::TextureAtlas()
    {
        texture = 0;
    }

    TextureAtlas::~TextureAtlas()
    {

        free(imageName);
        free(format);
        free(filter1);
        free(filter2);

        std::map<std::string, TextureRegion*>::iterator iter;
        for (iter = regions.begin(); iter != regions.end(); ++iter)
        {
            TextureRegion *region = static_cast<TextureRegion*>(iter->second);
            iter->second = NULL;
            delete region;
        }

        regions.clear();
        delete texture;

    }

}
