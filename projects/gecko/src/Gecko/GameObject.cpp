#include "Gecko/PCH.hpp"

#include "Gecko/GameObject.hpp"
#include "Gecko/Scene.hpp"

namespace Gecko
{
    GameObject::GameObject(std::weak_ptr<Scene> scene, const std::string& name) : sceneManager(sceneManager)
    {
        sceneManager = scene.lock()->getSceneManager();

        entity = sceneManager->createEntity(name);

        sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
        sceneNode->attachObject(entity);
    }

    GameObject::~GameObject()
    {
        sceneManager->destroySceneNode(sceneNode);
        sceneManager->destroyEntity(entity);
    }

    Ogre::Entity* GameObject::getEntity() const
    {
        return entity;
    }

    Ogre::SceneNode* GameObject::getSceneNode() const
    {
        return sceneNode;
    }
}
