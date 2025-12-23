#pragma once

#include "PCH.hpp"

namespace Gecko
{
    class Scene;

    class GameObject
    {
    public:
        GameObject(std::weak_ptr<Scene> scene, const std::string& name);

        ~GameObject();

        Ogre::Entity* getEntity() const;
        Ogre::SceneNode* getSceneNode() const;

    protected:
        Ogre::SceneManager* sceneManager;
        Ogre::Entity* entity;
        Ogre::SceneNode* sceneNode;
    };
}
