#pragma once

#include "Gecko/PCH.hpp"

namespace Gecko
{
    class Scene
    {
    public:
        Scene(Ogre::Root* root);

        Ogre::Root* getRoot() const;
        Ogre::SceneManager* getSceneManager() const;

    protected:
        Ogre::Root* root;
        Ogre::SceneManager* sceneManager;
    };
}
