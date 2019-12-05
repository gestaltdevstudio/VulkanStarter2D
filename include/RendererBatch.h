#ifndef RENDERERBATCH_H_INCLUDED
#define RENDERERBATCH_H_INCLUDED

#include "TextureAtlas.h"

namespace GGE {


    class RendererBatch {
        public:
            RendererBatch(uint16_t maxDrawables=1000);
            ~RendererBatch();
            void begin();
            void end();
            void draw(const Texture *texture, const AtlasRegion* region, float x, float y, float originX, float originY, float width, float height,
            float scaleX, float scaleY, float rotation);


        private:
            uint16_t renderCalls;
            uint64_t totalRenderCalls;
            float* vertices;
            Texture *lastTexture;

    };

}

#endif // RENDERERBATCH_H_INCLUDED
