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
            ~Text();
            void initText(const char * _textName, Font *_textFont, std::string _textureRegionName, TextureAtlas* _textureAtlas, int _x, int _y);

            void setText(std::string _text);

//            inline void setPosition(int _x, int _y) {position.x = _x; position.y = _y; updateText(); };
//            inline void setScaleX(float _x) { scaleX = _x; updateText(); }
//            inline void setScaleY(float _y) { scaleY = _y; updateText(); }
//            inline void setVisible(bool _visible) { visible = _visible; updateText(); }
//            inline bool isVisible() { return visible; }
            inline std::string getName() { return textName; }

//            inline Point getPosition() { return position; }
//            inline float getScaleX() { return scaleX; }
//            inline float getScaleY() { return scaleY; }
            inline Font* getFont() { return font; }
            inline TextureAtlas* getTextureAtlas() { return textureAtlas; }
            inline std::string getTextureRegionName() { return textureRegionName; }
            inline std::vector<CharInfo> getCharsInfo() { return charsInfo; }
//            inline void setColor(Vector4 _color) { color = _color; }
//            inline Vector4 getColor() { return color; }
            inline void setTextAlign(TextAlign _textAlign) { textAlign = _textAlign; updateText(); }
            inline TextAlign getTextAlign() { return textAlign; }

            void updateText();

        protected:

            TextAlign               textAlign;
            std::string             textName;
            float                   textSize;
//            float                   scaleX, scaleY;
            Font                    *font;
			std::string             textToPrint;
			std::string             textPrinted;
            Texture                 *texture;
//            Vector4                 color;

            std::vector<CharInfo>   charsInfo;
            std::string             textureRegionName;
            TextureAtlas            *textureAtlas;
//            Point                   position;
            bool                    visible;


    };

}

#endif // TEXT_H_INCLUDED
