#ifndef GRAPHICS_MANAGER_H_INCLUDED
#define GRAPHICS_MANAGER_H_INCLUDED

#include "Renderer.h"
#include "Definitions.h"
#include "Sprite.h"
#include "UIObject.h"
//#include "Text.h"
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
#include <list>
#include <algorithm>

namespace GGE
{

    class Text;
    class Renderer;

    // Comparison function to Sprites Z Order
    struct SpriteZOrderCompare {
        bool operator() (const GraphicElement* left, const GraphicElement* right) const {
           return left->zOrder < right->zOrder;
        }
    };

    class GraphicsManager
    {

        public:

            static GraphicsManager *getInstance()
            {
               if (!GraphicsManager::instance) GraphicsManager::instance = new GraphicsManager();
               return GraphicsManager::instance;
            }

            void	         onRender(float deltaTime);
            void	 		 onRenderFinish();
            void             onSceneFinish();
            void             addGraphicElement(GraphicElement *graphicElement);
            void             removeGraphicElement(GraphicElement *graphicElement);
            void             doGraphics(float deltaTime);
            void             destroy();
            void             shakeCamera();
            void             cameraUpdate(float delta);
            void             setCameraPosition(float x, float y);
            void             reset();

            inline void      setAnimationsPaused(bool _animationsPaused) { animationsPaused = _animationsPaused; };
            void sortSpritesbyZOrder();

            inline Renderer* getRenderer() { return renderer; }
            void             prepare();

        private:

            static GraphicsManager *instance;
            GraphicsManager();

            std::list<GraphicElement*>              graphicElements;


            bool                                    animationsPaused;

            Renderer*                               renderer;

    };

}




#endif // GRAPHICS_MANAGER_H_INCLUDED
