#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "Font.h"
#include "TextureAtlas.h"
#include <vector>
#include "GraphicElement.h"
#if defined(__ANDROID__)
 #include "OS_ANDROID.h"
#elif __APPLE__
 #include "TargetConditionals.h"
 #if TARGET_OS_OSX
  #include "OS_GLFW.h"
 #else
  #include "OS_iOS.h"
 #endif
#else
 #include "OS_GLFW.h"
#endif

namespace GGE
{

    struct CharInfo
    {
        Rectangle  quad;
        Rectangle  clip;
    };

    enum TextAlign
    {
        TEXT_ALIGN_CENTER = 0,
        TEXT_ALIGN_LEFT = 1,
    };

    class Text : public Drawable
    {

        public:
            Text();
            virtual ~Text();
            void initText(const char * _textName, Font *_textFont, const std::string &_textureRegionName, TextureAtlas* _textureAtlas, int _x, int _y);

            void setText(const std::string &_text);

            inline std::string getName() const { return textName; }

            inline Font* getFont() { return font; }
            inline TextureAtlas* getTextureAtlas() { return textureAtlas; }
            inline std::string getTextureRegionName() const { return textureRegionName; }
            inline std::vector<CharInfo> getCharsInfo() { return charsInfo; }

            inline void setTextAlign(TextAlign _textAlign) { textAlign = _textAlign; updateText(); }
            inline TextAlign getTextAlign() { return textAlign; }

            void updateText();

        protected:

            TextAlign               textAlign;
            std::string             textName;
            float                   textSize;

            Font                    *font;
			std::string             textToPrint;
			std::string             textPrinted;
            Texture                 *texture;


            std::vector<CharInfo>   charsInfo;
            std::string             textureRegionName;
            TextureAtlas            *textureAtlas;

            bool                    visible;


    };

}

#endif // TEXT_H_INCLUDED
