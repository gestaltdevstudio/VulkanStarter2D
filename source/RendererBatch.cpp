#include "../include/RendererBatch.h"

namespace GGE {

    RendererBatch::RendererBatch(uint16_t maxDrawables) {
        vertices = new float[maxDrawables * 5 * 4];

    }

    RendererBatch::~RendererBatch() {


    }

    void RendererBatch::begin() {

    }

    void RendererBatch::end() {

    }

    void RendererBatch::draw(const Texture *texture, const AtlasRegion* region, float x, float y, float originX, float originY, float width, float height,
		float scaleX, float scaleY, float rotation) {



    }

}
