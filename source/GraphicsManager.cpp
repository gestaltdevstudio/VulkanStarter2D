#include "../include/GraphicsManager.h"

namespace GGE
{
    GraphicsManager* GraphicsManager::instance = 0;

    GraphicsManager::GraphicsManager()
	{
	    sprites.empty();
	    animationsPaused = false;

	}

	void GraphicsManager::initGraphics()
	{

        renderer = new Renderer(1000);

	}

	void GraphicsManager::doGraphics(float deltaTime)
	{
        renderer->onRenderStart();

        for(std::list<GraphicElement*>::iterator it = graphicElements.begin(); it != graphicElements.end(); ++it)
        {

            Sprite *sprite = NULL;
//            Text *text = NULL;
//            UIObject *uiObject = NULL;
            sprite = dynamic_cast<Sprite*>(*it);
            if (sprite)
            {
                if (sprite->isVisible()) {

                    Drawable *drawable;
                    if (!sprite->getCurrentAnimationName().empty())
                    {
                        if (!animationsPaused) {
                            sprite->updateCurrentAnimation(deltaTime);
                        }
                        drawable = sprite->getCurrentAnimation()->getCurrentDrawable(sprite->getElapsedTime(), sprite->getAnimationPlayMode());
                    }
                    else
                    {
                        drawable = reinterpret_cast<Drawable*>(sprite);
                    }

                    renderer->renderDrawable(drawable);

                }
            }
//            else
//            {
//                text = dynamic_cast<Text*>(*it);
//                if (text && text->isVisible())
//                {
//                    renderer->renderText(text);
//                }
//                else
//                {
//                    uiObject = dynamic_cast<UIObject*>(*it);
//                    if (uiObject && uiObject->isVisible())
//                    {
//                        renderer->renderTexture(uiObject->getPosition().x, uiObject->getPosition().y, uiObject->getDrawable());
//                    }
//                }
//            }

        }

        renderer->onRenderFinish();
    }



    void GraphicsManager::addSprite(std::string objectName, Sprite *_object)
    {
         sprites.insert(std::make_pair(objectName, _object));
         graphicElements.push_back(_object);

    }

    void GraphicsManager::removeSprite(std::string objectName)
    {
        if (sprites.find(objectName) != sprites.end())
        {
            sprites.erase(objectName);
            graphicElements.erase(std::remove(graphicElements.begin(), graphicElements.end(), sprites[objectName]), graphicElements.end());
        }
    }

    void GraphicsManager::addText(std::string objectName, Text *_object)
    {
         texts.insert(std::make_pair(objectName, _object));
         graphicElements.push_back(_object);

    }

    void GraphicsManager::removeText(std::string objectName)
    {
        if (texts.find(objectName) != texts.end())
        {
            texts.erase(objectName);
            graphicElements.erase(std::remove(graphicElements.begin(), graphicElements.end(), texts[objectName]), graphicElements.end());
        }
    }

    void GraphicsManager::addUIObject(std::string objectName, UIObject *_object)
    {
         uiObjects.insert(std::make_pair(objectName, _object));
         graphicElements.push_back(_object);

    }

    void GraphicsManager::removeUIObject(std::string objectName)
    {
        if (uiObjects.find(objectName) != uiObjects.end())
        {
            uiObjects.erase(objectName);
            graphicElements.erase(std::remove(graphicElements.begin(), graphicElements.end(), texts[objectName]), graphicElements.end());
        }
    }

    void GraphicsManager::sortSpritesbyZOrder()
    {
        graphicElements.sort(SpriteZOrderCompare());
    }

	void GraphicsManager::destroy()
	{

        delete renderer;

	}

}
