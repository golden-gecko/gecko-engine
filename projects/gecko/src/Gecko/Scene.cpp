#include "Gecko/PCH.hpp"

#include "Gecko/Scene.hpp"

namespace Gecko
{
    Scene::Scene(Ogre::Root* root) : root(root)
    {
        sceneManager = root->createSceneManager();

        Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(sceneManager);
    }

    Ogre::Root* Scene::getRoot() const
    {
        return root;
    }

    Ogre::SceneManager* Scene::getSceneManager() const
    {
        return sceneManager;
    }
}
