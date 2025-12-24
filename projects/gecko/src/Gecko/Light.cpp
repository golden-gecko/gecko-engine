#include "Gecko/PCH.hpp"

#include "Gecko/Light.hpp"
#include "Gecko/Scene.hpp"

namespace Gecko
{
    Light::Light(std::weak_ptr<Scene> scene, const std::string& name) : scene(scene)
    {
        sceneManager = scene.lock()->getSceneManager();

        light = sceneManager->createLight(name);
        light->setCastShadows(false);
        light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);

        sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
        sceneNode->attachObject(light);
        sceneNode->lookAt(Ogre::Vector3f(-1.0f, -1.0f, -1.0f), Ogre::Node::TransformSpace::TS_PARENT);
    }

    Light::~Light()
    {
        sceneManager->destroySceneNode(sceneNode);
        sceneManager->destroyLight(light);
    }
}
