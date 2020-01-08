#include "../include/Text.h"

namespace GGE
{

    Text::Text()
    {
		textToPrint = "";
		textPrinted = "";
		visible = false;
		scaleX = scaleY = 1.0f;
//        color.r = color.g = color.b = color.a = 1;
//        position.x = position.y = 0;
        charsInfo.empty();
        textAlign = TEXT_ALIGN_LEFT;
    }


    Text::~Text()
    {
    }

    void Text::setText(std::string _text)
    {
        if (_text.length() == 0 || _text.compare("") == 0)
        {
            _text = " ";
        }
        textToPrint = _text;

    };

    void Text::initText(const char * _textName, Font *_textFont, std::string _textureRegionName, TextureAtlas* _textureAtlas, int _x, int _y)
    {
        if (_textureAtlas->regions.find(_textureRegionName) == _textureAtlas->regions.end())
        {
            OS::getInstance()->alert("Can't initiate Text object", _textName);
        }
        else
        {
            textName = _textName;
            textureAtlas = _textureAtlas;
            textureRegionName = _textureRegionName;
            x = _x;
            y = _y;
            font = _textFont;
            textSize = 96;

        }
    }

    void Text::updateText()
    {
        if (!textPrinted.empty() || !textToPrint.empty())
        {

            TextureRegion *atlasRegion= static_cast<TextureRegion*>(textureAtlas->regions.at(textureRegionName));

            textPrinted = textToPrint;
            int length = textPrinted.length();

            charsInfo.clear();
            int letterX = 0;
            int xAlignOffset = 0;

            // Calculating xOffset
            int biggerLength = 0;
            if (textAlign == TEXT_ALIGN_CENTER)
            {
                for (int i=0; i<length; i++)
                {
                    char character = textPrinted[i];

                    if (character == '/')
                    {
                        biggerLength = xAlignOffset > biggerLength ? xAlignOffset : biggerLength;
                    }
                    else
                    {
                        FontChar fontChar = font->fontChars[(int)character];
                        xAlignOffset += round(fontChar.xadvance * scaleX);
                    }
                }
            }

            short lineBreakOffset = 0;
            for ( int i=0 ; i<length ; i++ ){
                char character = textPrinted[i];

                // LineBreak
                if (character == '/')
                {
                    lineBreakOffset += 40;
                    letterX = 0;
                }
                else
                {
                    FontChar fontChar = font->fontChars[(int)character];

                    float uv_x = (float) (atlasRegion->x + (float) fontChar.x) / textureAtlas->width;
                    float uv_y = (float) (atlasRegion->y + (float) fontChar.y) / textureAtlas->height;
                    float yOffset = (float) fontChar.yoffset;// / font->textureWidth;
                    float width = (float) fontChar.width / textureAtlas->width;
                    float height = (float) fontChar.height / textureAtlas->height;

                    float vertexWidth = (float) fontChar.width;// / (float) font->textureWidth;
                    float vertexHeight = (float) fontChar.height;// / (float) font->textureHeight;

//                    glm::vec2 vertex_up_left    = glm::vec2( letterX                         , y - (vertexHeight * (textSize * scaleY)) - (yOffset * (textSize * scaleY)));
//                    glm::vec2 vertex_up_right   = glm::vec2( letterX + (vertexWidth * (textSize * scaleX)), y - (vertexHeight * textSize * scaleY) - (yOffset * (textSize * scaleY)));
//                    glm::vec2 vertex_down_right = glm::vec2( letterX + (vertexWidth * (textSize * scaleX)), y - (yOffset * (textSize * scaleY))   );
//                    glm::vec2 vertex_down_left  = glm::vec2( letterX                         , y - (yOffset * (textSize * scaleY))   );

                    Rectangle quad;
//
//               glm::vec2 vertex_up_left    = glm::vec2( letterX                         , y - (vertexHeight * (textSize * scaleY)) - (yOffset * (textSize * scaleY)));
//                glm::vec2 vertex_up_right   = glm::vec2( letterX + (vertexWidth * (textSize * scaleX)), y - (vertexHeight * textSize * scaleY) - (yOffset * (textSize * scaleY)));
//                glm::vec2 vertex_down_right = glm::vec2( letterX + (vertexWidth * (textSize * scaleX)), y - (yOffset * (textSize * scaleY))   );
//                glm::vec2 vertex_down_left  = glm::vec2( letterX                         , y - (yOffset * (textSize * scaleY))   );

                    quad.x = x - (xAlignOffset/2) + (letterX + fontChar.xoffset);
                    quad.y = lineBreakOffset + (y + (yOffset * scaleY));
                    quad.w = (vertexWidth - fontChar.xoffset) * scaleX;
                    quad.h = vertexHeight * scaleY;

                    Rectangle clip;

                    clip.x = uv_x;
                    clip.y = uv_y;
                    clip.w = width;
                    clip.h = height;

                    CharInfo charInfo;
                    charInfo.quad = quad;
                    charInfo.clip = clip;

                    charsInfo.push_back(charInfo);
                    letterX += fontChar.xadvance * scaleX ;
                }

            }

        }

    }

}
