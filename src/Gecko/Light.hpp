#pragma once

#include "Gecko/Gecko.hpp"

namespace Gecko
{
    class Scene;

    class Light
    {
    public:
        Light(Scene* scene, const std::string& name);

        virtual ~Light();

    protected:
        Ogre::SceneManager* sceneManager = nullptr;
        Ogre::Light* light = nullptr;
        Ogre::SceneNode* sceneNode = nullptr;
    };
}
