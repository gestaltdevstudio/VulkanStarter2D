#ifndef GAMEVIEW_H_INCLUDED
#define GAMEVIEW_H_INCLUDED

#include "View.h"
#include "TextureAtlas.h"
#include "Sprite.h"
//#include "Text.h"
#include "Button.h"
#include "GameModel.h"

namespace GGE
{

    class GameView : public View
    {

        public:
            GameView(Screen *_screen, GameModel *_gameModel);
            void finishView();
            void initView();
            void step(float deltaTime);

        protected:
            int runOnce = 0;
            GameModel *gameModel;
            TextureAtlas *ta, *ta2;

            Sprite *playerSprite;
            std::vector<Sprite *> playerSprite2;
            Animation *animation;
            Animation *animation2;
            Sprite *s2;
            Font *f;
            Text *t;
            Button *exitButton;

#if !defined(GGE_DESKTOP)
            Button *leftButton;
            Button *rightButton;
            Button *jumpButton;
#endif

    };

}

#endif // GAMEVIEW_H_INCLUDED
