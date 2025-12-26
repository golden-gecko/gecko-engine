#pragma once

#include "Gecko/Gecko.hpp"

namespace Gecko
{
    class Scene
    {
    public:
        Scene(Ogre::Root* root);
        
        virtual ~Scene();

        Ogre::Root* getRoot() const;
        Ogre::SceneManager* getSceneManager() const;

    protected:
        Ogre::Root* root = nullptr;
        Ogre::SceneManager* sceneManager = nullptr;
    };
}
