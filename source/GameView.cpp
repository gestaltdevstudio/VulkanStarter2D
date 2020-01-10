#include "../include/GameView.h"

namespace GGE
{

    GameView::GameView(Screen *_screen, GameModel *_gameModel) : View(_screen)
    {
        gameModel = _gameModel;
    }

    void GameView::initView()
    {

        ta = new TextureAtlas();

        const resourceFile *rfMenuAtlas = ResourcesManager::getInstance()->loadCompressedFile("game.atlas");
        const resourceFile *rfMenuImage = ResourcesManager::getInstance()->loadCompressedFile("game.png");
        ta->loadTextureAtlas(rfMenuAtlas, rfMenuImage);
        delete rfMenuImage;
        delete rfMenuAtlas;

        ta2 = new TextureAtlas();

        const resourceFile *rfMenuAtlas2 = ResourcesManager::getInstance()->loadCompressedFile("game2.atlas");
        const resourceFile *rfMenuImage2 = ResourcesManager::getInstance()->loadCompressedFile("game2.png");
        ta2->loadTextureAtlas(rfMenuAtlas2, rfMenuImage2);
        delete rfMenuImage2;
        delete rfMenuAtlas2;

//        sh = new Shader();
//        const resourceFile *rfVertShader = ResourcesManager::getInstance()->loadCompressedFile("shader.vert");
//        const resourceFile *rfFragShader = ResourcesManager::getInstance()->loadCompressedFile("shader.frag");
//        sh->setShaderID(GraphicsUtils::loadShaders(rfVertShader, rfFragShader));
//        if (!sh->getShaderID())
//            return;

//        delete rfVertShader;
//        delete rfFragShader;

        playerSprite = new Sprite("Player");
        playerSprite->loadRegion("dogAnim2", ta);
        Animation *animation = new Animation();
        std::vector<std::string> frames;
        frames.push_back("dogAnim2");
        frames.push_back("dogAnim3");
        frames.push_back("dogAnim4");
        frames.push_back("dogAnim5");
        frames.push_back("dogAnim6");
        frames.push_back("dogAnim7");
        frames.push_back("dogAnim8");
        frames.push_back("dogAnim9");
        animation->loadFrames(ta, 1.0/8, frames);
        playerSprite->addAnimation("Idle", animation);
        playerSprite->setCurrentAnimationName("Idle", ANIM_LOOP_PINGPONG);
//        playerSprite->setShader(sh);
        playerSprite->setIsVisible(true);
        playerSprite->setEntity(gameModel->getPlayer());
        playerSprite->setFlippedX(true);
//        playerSprite->setRotation(45.f);
        playerSprite->setX(-SCREEN_X/2 + playerSprite->getTextureRegion()->width/2);
        playerSprite->setY(SCREEN_Y/2 - playerSprite->getTextureRegion()->height/2);
        GraphicsManager::getInstance()->addGraphicElement(playerSprite);

        playerSprite2 = new Sprite("Player2");
        playerSprite2->loadRegion("dogAnim2", ta);
        Animation *animation2 = new Animation();
        std::vector<std::string> frames2;
        frames2.push_back("dogAnim2");
        frames2.push_back("dogAnim3");
        frames2.push_back("dogAnim4");
        frames2.push_back("dogAnim5");
        frames2.push_back("dogAnim6");
        frames2.push_back("dogAnim7");
        frames2.push_back("dogAnim8");
        frames2.push_back("dogAnim9");
        animation2->loadFrames(ta, 1.0/8, frames2);
        playerSprite2->addAnimation("Idle", animation2);
        playerSprite2->setCurrentAnimationName("Idle", ANIM_LOOP_PINGPONG);
//        playerSprite->setShader(sh);
        playerSprite2->setIsVisible(true);
//        playerSprite2->setFlippedX(true);
//        playerSprite->setRotation(45.f);
        playerSprite2->setX(0);
        playerSprite2->setY(0);
        GraphicsManager::getInstance()->addGraphicElement(playerSprite2);

        s2 = new Sprite("Bone");
        s2->loadRegion("bone", ta2);
        s2->setIsVisible(true);
        s2->setX(-SCREEN_X/2 + s2->getTextureRegion()->width/2);
        s2->setY(-SCREEN_Y/2 + s2->getTextureRegion()->height/2);
        GraphicsManager::getInstance()->addGraphicElement(s2);

        exitButton = new Button();
        Drawable *d = new Drawable();
        d->loadRegion("exitButton", ta2);
        d->setIsVisible(true);
        exitButton->setDrawable(d);
        exitButton->setPosition(SCREEN_X/2 - exitButton->getDimension()->x/2,
                            -SCREEN_Y/2 + exitButton->getDimension()->y/2);

        GraphicsManager::getInstance()->addGraphicElement(exitButton);
//
//#if !defined(GGE_DESKTOP)
//        leftButton = new Button();
//        Drawable *ld = new Drawable();
//        ld->loadRegion("arrow", ta);
//        ld->setShader(sh);
//        ld->setIsVisible(true);
//        leftButton->setDrawable(ld);
//        leftButton->setPosition(-SCREEN_X/2 + 200,
//                                -SCREEN_Y/2 + 100);
//
//        GraphicsManager::getInstance()->addUIObject("Left", leftButton);
//
//        rightButton = new Button();
//        Drawable *rd = new Drawable();
//        rd->loadRegion("arrow", ta);
//        rd->setShader(sh);
//        rd->setIsVisible(true);
//        rd->setRotation(180);
//        rightButton->setDrawable(rd);
//        rightButton->setPosition(-SCREEN_X/2 + 400,
//                                -SCREEN_Y/2 + 100);
//
//        GraphicsManager::getInstance()->addUIObject("Right", rightButton);
//
//        jumpButton = new Button();
//        Drawable *jd = new Drawable();
//        jd->loadRegion("arrow", ta);
//        jd->setShader(sh);
//        jd->setIsVisible(true);
//        jd->setRotation(270);
//        jumpButton->setDrawable(jd);
//        jumpButton->setPosition(SCREEN_X/2 - 220,
//                                -SCREEN_Y/2 + 100);
//
//        GraphicsManager::getInstance()->addUIObject("Jump", jumpButton);
//#endif
//
//        textSh = new Shader();
//        const resourceFile *rfTextVertShader = ResourcesManager::getInstance()->loadCompressedFile("textShader.vert");
//        const resourceFile *rfTextFragShader = ResourcesManager::getInstance()->loadCompressedFile("textShader.frag");
////        textSh->setShaderID(GraphicsUtils::loadShaders(rfTextVertShader, rfTextFragShader));
//
//        delete rfTextVertShader;
//        delete rfTextFragShader;
//
        f = new Font();
        const resourceFile *fontFile = ResourcesManager::getInstance()->loadCompressedFile("pressStart2P.fnt");
        f->loadFont(fontFile);
//
        t = new Text();
        t->initText("Text", f, "pressStart2P", ta2, 0, 0);
        t->setText("nsaefOUGH BF Soyjua.,PfAf");
//        t->setX(-400);
//        t->setY(-100);
//        t->setScaleX(1.5);
//        t->setScaleY(1.5);
//        t->setFlippedX(true);
//        t->setFlippedY(true);
        t->updateText();
        t->setRotation(-45);
        t->setTextAlign(TEXT_ALIGN_CENTER);
        GraphicsManager::getInstance()->addGraphicElement(t);
        t->setIsVisible(true);
//
//
        delete fontFile;


    }

    void GameView::step(float deltaTime)
    {

        Point mouseCoord = OS::getInstance()->getMouseCoord();
//
//        playerSprite->setX(playerSprite->getEntity()->getPosition()->x);
//        playerSprite->setY(playerSprite->getEntity()->getPosition()->y);
//
//        if (playerSprite->getEntity()->getNextPosition()->x < playerSprite->getEntity()->getPreviousPosition()->x)
//        {
//            playerSprite->setFlipedX(true);
//        }
//        else if (playerSprite->getEntity()->getNextPosition()->x > playerSprite->getEntity()->getPreviousPosition()->x)
//        {
//            playerSprite->setFlipedX(false);
//        }
//
//
        if (exitButton->isClicked(mouseCoord))
        {
            OS::getInstance()->setRunning(false);
        }
//#if !defined(GGE_DESKTOP)
//            if (leftButton->isClicked(OS::getInstance()->getInputCoord(LEFT_HAND)))
//            {
//                InputSystem::getInstance()->keyPressed(GGE_LEFT);
//            } else {
//                InputSystem::getInstance()->keyReleased(GGE_LEFT);
//            }
//            if (rightButton->isClicked(OS::getInstance()->getInputCoord(LEFT_HAND)))
//            {
//                InputSystem::getInstance()->keyPressed(GGE_RIGHT);
//            } else {
//                InputSystem::getInstance()->keyReleased(GGE_RIGHT);
//            }
//            if (jumpButton->isClicked(OS::getInstance()->getInputCoord(RIGHT_HAND)))
//            {
//                InputSystem::getInstance()->keyPressed(GGE_UP);
//            } else {
//                InputSystem::getInstance()->keyReleased(GGE_UP);
//            }
//#endif

        GraphicsManager::getInstance()->doGraphics(deltaTime);

    }

    void GameView::finishView()
    {

        delete playerSprite;
        delete playerSprite2;
//        delete s2;
//        delete sh;
//        delete textSh;
        delete ta;
        delete ta2;
        delete f;
//        delete t;
//#if !defined(GGE_DESKTOP)
//        delete leftButton;
//        delete rightButton;
//        delete jumpButton;
//#endif
//        delete exitButton;

    }

}
