#include "../include/GraphicsManager.h"

namespace GGE
{
    GraphicsManager* GraphicsManager::instance = 0;

    GraphicsManager::GraphicsManager()
	{
        renderer = new Renderer(1000);

	}

	void GraphicsManager::reset()
	{
	    graphicElements.clear();
	    animationsPaused = false;
	}

	void GraphicsManager::prepare()
	{
        renderer->activeTextures.clear();
        for(std::list<GraphicElement*>::iterator it = graphicElements.begin(); it != graphicElements.end(); ++it)
        {
            Text *text = NULL;
            text = dynamic_cast<Text*>(*it);
            Drawable *drawable = NULL;
            drawable = dynamic_cast<Drawable*>(*it);
            UIObject *uiObject = NULL;
            uiObject = dynamic_cast<UIObject*>(*it);

            Texture* texture = NULL;

            if (text)
            {
                texture = text->getTextureAtlas()->texture;
            }
            else if (drawable)
            {
                texture = drawable->getTextureRegion()->textureAtlas->texture;
            }
            else if (uiObject)
            {
                texture = uiObject->getDrawable()->getTextureRegion()->textureAtlas->texture;
            }

            if (std::find(renderer->activeTextures.begin(), renderer->activeTextures.end(), texture) == renderer->activeTextures.end())
            {
                renderer->activeTextures.push_back(texture);
            }
            if (texture && renderer->activeTextures.empty())
            {
                renderer->activeTextures.push_back(texture);
            }
        }
        renderer->prepare();
	}

	void GraphicsManager::doGraphics(float deltaTime)
	{
        renderer->onRenderStart();

        for(std::list<GraphicElement*>::iterator it = graphicElements.begin(); it != graphicElements.end(); ++it)
        {

            Sprite *sprite = NULL;

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

            }
            else if (drawable)
            {
                if (drawable->isVisible()) {
                    renderer->renderDrawable(drawable->getTextureRegion(),
                    drawable->getX(), drawable->getY(), drawable->getScaleX(), drawable->getScaleY(), drawable->getRotation(), drawable->isFlippedX(), drawable->isFlippedY(),
                    drawable->getColor());
                }
            }

        }

        for(std::list<GraphicElement*>::iterator it = graphicElements.begin(); it != graphicElements.end(); ++it)
        {

            UIObject *uiObject = NULL;
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
        delete instance;
        instance = NULL;
	}

}
