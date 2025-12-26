
#include "Gecko/App.hpp"
#include "Gecko/Camera.hpp"
#include "Gecko/Input.hpp"

Gecko::App* Ogre::Singleton<Gecko::App>::msSingleton = nullptr;

namespace Gecko
{
    App::App()
    {
        context = new OgreBites::ApplicationContext();
        context->initApp();

        if (context->getRoot()->restoreConfig() == false)
        {
            context->getRoot()->showConfigDialog(OgreBites::getNativeConfigDialog());
        }

        context->getRoot()->addFrameListener(this);
    }

    App::~App()
    {
        context->closeApp();
    }

    void App::run()
    {
        context->getRoot()->startRendering();
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
        return context;
    }

    Ogre::Root* App::getRoot() const
    {
        return context->getRoot();
    }

    Ogre::RenderWindow* App::getRenderWindow() const
    {
        return context->getRenderWindow();
    }

    size_t App::getRenderWindowHandle() const
    {
        size_t windowHadle = 0;

        getRenderWindow()->getCustomAttribute("WINDOW", &windowHadle);

        return windowHadle;
    }

    void App::setCamera(std::weak_ptr<Camera> camera)
    {
        context->getRenderWindow()->addViewport(camera.lock()->getCamera())->setBackgroundColour(Ogre::ColourValue::White);
    }
}
