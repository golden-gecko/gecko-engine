#include "Gecko/PCH.hpp"

#include "Gecko/App.hpp"
#include "Gecko/Camera.hpp"
#include "Gecko/Input.hpp"

Gecko::App* Ogre::Singleton<Gecko::App>::msSingleton = nullptr;

namespace Gecko
{
    App::App()
    {
        ctx = new OgreBites::ApplicationContext();
        ctx->initApp();

        if (ctx->getRoot()->restoreConfig() == false)
        {
            ctx->getRoot()->showConfigDialog(OgreBites::getNativeConfigDialog());
        }

        ctx->getRoot()->addFrameListener(this);
    }

    App::~App()
    {
        ctx->closeApp();
    }

    void App::run()
    {
        ctx->getRoot()->startRendering();
    }

    bool App::frameStarted(const Ogre::FrameEvent& evt)
    {
        Input::getSingleton().capture();

        if (Input::getSingleton().isKeyDown(OIS::KeyCode::KC_ESCAPE))
        {
            return false;
        }

        Camera::getSingleton().update(evt.timeSinceLastFrame);

        return true;
    }

    bool App::frameEnded(const Ogre::FrameEvent& evt)
    {
        return true;
    }

    OgreBites::ApplicationContext* App::getContext() const
    {
        return ctx;
    }

    Ogre::Root* App::getRoot() const
    {
        return ctx->getRoot();
    }

    Ogre::RenderWindow* App::getRenderWindow() const
    {
        return ctx->getRenderWindow();
    }

    size_t App::getRenderWindowHandle() const
    {
        size_t windowHadle = 0;

        getRenderWindow()->getCustomAttribute("WINDOW", &windowHadle);

        return windowHadle;
    }

    void App::setCamera(std::weak_ptr<Camera> camera)
    {
        ctx->getRenderWindow()->addViewport(camera.lock()->getCamera())->setBackgroundColour(Ogre::ColourValue::White);
    }
}
