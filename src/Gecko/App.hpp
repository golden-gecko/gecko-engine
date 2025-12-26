#pragma once

#include "Gecko/Gecko.hpp"

namespace Gecko
{
    class Camera;

    class App : public Ogre::Singleton<App>, public Ogre::FrameListener
    {
    public:
        // Ogre::FrameListener
        bool frameStarted(const Ogre::FrameEvent& evt) override;
        bool frameEnded(const Ogre::FrameEvent& evt) override;

    public:
        App();

        virtual ~App();

        void run();

        OgreBites::ApplicationContext* getContext() const;
        Ogre::Root* getRoot() const;
        Ogre::RenderWindow* getRenderWindow() const;
        size_t getRenderWindowHandle() const;

        void setCamera(std::weak_ptr<Camera> camera);

    protected:
        OgreBites::ApplicationContext* context = nullptr;
    };
}
