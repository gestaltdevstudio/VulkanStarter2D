#include "../include/GameScreen.h"

namespace GGE
{

    GameScreen::GameScreen()
    {
        fixedDeltaTime = 0.016;

        gameModel = new GameModel();
        gameView = new GameView(this, gameModel);

        gameModel->initModel();
    }

    GameScreen::~GameScreen()
    {

    }

    void GameScreen::initScreen()
    {

        gameView->initView();
        accumulator = 0;
        OS::getInstance()->setRunning(true);
    }

    void GameScreen::render(float deltaTime)
    {

#if defined(GGE_DESKTOP)
        if (InputSystem::getInstance()->isKeyDown(KeyCode::GGE_ESCAPE) && OS::getInstance()->isFullScreen())
        {
            OS::getInstance()->toggleFullScreen();
            InputSystem::getInstance()->keyReleased(KeyCode::GGE_ESCAPE);
        }
#endif

        if (deltaTime > 0.25)
            deltaTime = 0.25;

        accumulator += deltaTime;

        while (accumulator >= fixedDeltaTime)
        {
            gameModel->step(fixedDeltaTime);
            accumulator -= fixedDeltaTime;
        }

        gameModel->interpolate(accumulator / fixedDeltaTime);
        gameModel->checkCollision();
        gameView->step(deltaTime);

    }


    void GameScreen::show()
    {

#if defined (GGE_DESKTOP)
        GraphicsManager::getInstance()->getRenderer()->createContext();
        initScreen();
        GraphicsManager::getInstance()->prepare();
#endif
    }

    void GameScreen::pause()
    {
#if defined (__ANDROID__)
        GraphicsManager::getInstance()->reset();
        gameView->finishView();
#endif
    }

    void GameScreen::resume()
    {

#if defined (__ANDROID__)
        GraphicsManager::getInstance()->getRenderer()->createContext();
        initScreen();
        GraphicsManager::getInstance()->prepare();
#endif

    }

    void GameScreen::finish()
    {

#if defined (GGE_DESKTOP)
        GraphicsManager::getInstance()->reset();
        gameView->finishView();
#endif
        gameModel->finishModel();

        delete gameView;
        delete gameModel;

    }

}
