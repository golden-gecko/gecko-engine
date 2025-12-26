#include "Gecko/GameObject.hpp"
#include "Gecko/Scene.hpp"

namespace Gecko
{
    GameObject::GameObject(Scene* scene, const std::string& name, const std::string& mesh)
    {
        sceneManager = scene->getSceneManager();

        entity = sceneManager->createEntity(name, mesh);
        entity->getUserObjectBindings().setUserAny(Ogre::Any(this));
        entity->setCastShadows(true);

        sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
        sceneNode->attachObject(entity);
        sceneNode->getUserObjectBindings().setUserAny(Ogre::Any(this));
    }

    GameObject::~GameObject()
    {
        sceneManager->destroySceneNode(sceneNode);
        sceneManager->destroyEntity(entity);
    }

    void GameObject::update(float time)
    {
    }
    
    Ogre::SceneManager* GameObject::getSceneManager() const
    {
        return sceneManager;
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
