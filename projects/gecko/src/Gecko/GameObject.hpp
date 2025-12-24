#pragma once

#include "Gecko/PCH.hpp"

namespace Gecko
{
    class Scene;

    class GameObject
    {
    public:
        GameObject(Scene* scene, const std::string& name, const std::string& mesh);

        virtual ~GameObject();

        virtual void update(float time);

        Ogre::SceneManager* getSceneManager() const;
        Ogre::Entity* getEntity() const;
        Ogre::SceneNode* getSceneNode() const;

    protected:
        Ogre::SceneManager* sceneManager = nullptr;
        Ogre::Entity* entity = nullptr;
        Ogre::SceneNode* sceneNode = nullptr;
    };
}
