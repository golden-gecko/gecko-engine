#include "PCH.hpp"

namespace Gecko
{
    class Scene;

    class Light
    {
    public:
        Light(std::weak_ptr<Scene> scene, const std::string& name);

        ~Light();

    protected:
        std::weak_ptr<Scene> scene;

        Ogre::SceneManager* sceneManager;
        Ogre::Light* light;
        Ogre::SceneNode* sceneNode;
    };
}
