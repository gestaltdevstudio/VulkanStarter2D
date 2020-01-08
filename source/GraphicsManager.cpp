#include "../include/GraphicsManager.h"

namespace GGE
{
    GraphicsManager* GraphicsManager::instance = 0;

    GraphicsManager::GraphicsManager()
	{
	    graphicElements.empty();
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
//            UIObject *uiObject = NULL;
            sprite = dynamic_cast<Sprite*>(*it);
            Drawable *drawable = NULL;
            drawable = dynamic_cast<Drawable*>(*it);
            Text *text = NULL;
            text = dynamic_cast<Text*>(*it);
            if (sprite)
            {
                if (sprite->isVisible()) {

                    if (!sprite->getCurrentAnimationName().empty())
                    {
                        if (!animationsPaused) {
                            sprite->updateCurrentAnimation(deltaTime);
                        }
                        renderer->renderDrawable(sprite->getCurrentAnimation()->getCurrentTextureRegion(sprite->getElapsedTime(), sprite->getAnimationPlayMode()),
                        sprite->getX(), sprite->getY(), sprite->getScaleX(), sprite->getScaleY(), sprite->getRotation(), sprite->isFlippedX(), sprite->isFlippedY(),
                        sprite->getColor());
                    }
                    else
                    {
                        renderer->renderDrawable(sprite->getTextureRegion(),
                        sprite->getX(), sprite->getY(), sprite->getScaleX(), sprite->getScaleY(), sprite->getRotation(), sprite->isFlippedX(), sprite->isFlippedY(),
                        sprite->getColor());
                    }


                }
            }
            else if (text)
            {
                if (text && text->isVisible())
                {
                    renderer->renderText(text);
                }
//                else
//                {
//                    uiObject = dynamic_cast<UIObject*>(*it);
//                    if (uiObject && uiObject->isVisible())
//                    {
//                        renderer->renderTexture(uiObject->getPosition().x, uiObject->getPosition().y, uiObject->getDrawable());
//                    }
//                }
            }
            else if (drawable)
            {
                if (drawable->isVisible()) {
                    renderer->renderDrawable(drawable->getTextureRegion(),
                    drawable->getX(), drawable->getY(), drawable->getScaleX(), drawable->getScaleY(), drawable->getRotation(), drawable->isFlippedX(), drawable->isFlippedY(),
                    drawable->getColor());
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

        for(std::list<GraphicElement*>::iterator it = graphicElements.begin(); it != graphicElements.end(); ++it)
        {

            UIObject *uiObject = NULL;
//            Text *text = NULL;
//            UIObject *uiObject = NULL;
            uiObject = dynamic_cast<UIObject*>(*it);

            if (uiObject)
            {
                if (uiObject->getDrawable()->isVisible()) {
                    renderer->renderDrawable(uiObject->getDrawable()->getTextureRegion(),
                    uiObject->getPosition()->x, uiObject->getPosition()->y, uiObject->getDrawable()->getScaleX(),
                    uiObject->getDrawable()->getScaleY(), uiObject->getDrawable()->getRotation(), uiObject->getDrawable()->isFlippedX(), uiObject->getDrawable()->isFlippedY(),
                    uiObject->getDrawable()->getColor());
                }
            }

        }


        renderer->onRenderFinish();
    }

//
//
//    void GraphicsManager::addSprite(std::string objectName, Sprite *_object)
//    {
//         sprites.insert(std::make_pair(objectName, _object));
//         graphicElements.push_back(_object);
//
//    }
//
//    void GraphicsManager::removeSprite(std::string objectName)
//    {
//        if (sprites.find(objectName) != sprites.end())
//        {
//            sprites.erase(objectName);
//            graphicElements.erase(std::remove(graphicElements.begin(), graphicElements.end(), sprites[objectName]), graphicElements.end());
//        }
//    }
//
//    void GraphicsManager::addText(std::string objectName, Text *_object)
//    {
//         texts.insert(std::make_pair(objectName, _object));
//         graphicElements.push_back(_object);
//
//    }
//
//    void GraphicsManager::removeText(std::string objectName)
//    {
//        if (texts.find(objectName) != texts.end())
//        {
//            texts.erase(objectName);
//            graphicElements.erase(std::remove(graphicElements.begin(), graphicElements.end(), texts[objectName]), graphicElements.end());
//        }
//    }
//
//    void GraphicsManager::addUIObject(std::string objectName, UIObject *_object)
//    {
//         uiObjects.insert(std::make_pair(objectName, _object));
//         graphicElements.push_back(_object);
//
//    }
//
//    void GraphicsManager::removeUIObject(std::string objectName)
//    {
//        if (uiObjects.find(objectName) != uiObjects.end())
//        {
//            uiObjects.erase(objectName);
//            graphicElements.erase(std::remove(graphicElements.begin(), graphicElements.end(), texts[objectName]), graphicElements.end());
//        }
//    }

    void GraphicsManager::addGraphicElement(GraphicElement *graphicElement)
    {
         graphicElements.push_back(graphicElement);
    }

    void GraphicsManager::removeGraphicElement(GraphicElement *graphicElement)
    {
        graphicElements.erase(std::remove(graphicElements.begin(), graphicElements.end(), graphicElement), graphicElements.end());
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
