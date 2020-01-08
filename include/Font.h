#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include "ResourcesManager.h"
//#include "OS.h"

namespace GGE
{

    struct FontChar {

        int id;
        int x;
        int y;
        int width;
        int height;
        int xoffset;
        int yoffset;
        int xadvance;
        int page;
        int chnl;

    };


    class Font
    {
        public:
            Font();
            ~Font();
            void loadFont(const resourceFile *fileBuffer);
            FontChar *fontChars;
            int textureWidth;
            int textureHeight;
            inline int getOriginalSize() { return originalSize; }

        protected:
            int charCount;
            int originalSize;

    };

}

#endif // FONT_H_INCLUDED
