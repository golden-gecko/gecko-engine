#pragma once

#include "PCH.hpp"

namespace Gecko
{
    class Scene;

    class Camera : public Ogre::Singleton<Camera>
    {
    public:
        Camera(std::weak_ptr<Scene> scene, const std::string& name);

        ~Camera();

        Ogre::Camera* getCamera() const;

        void setPosition(const Ogre::Vector3f& position);

        void lookAt(const Ogre::Vector3f& position);
        void move(const Ogre::Vector3f& position);
        void rotate(const Ogre::Degree& yaw, const Ogre::Degree& pitch);

        void update(float time);

    protected:
        Ogre::SceneManager* sceneManager;
        Ogre::Camera* camera;
        Ogre::SceneNode* sceneNode;

        float speed = 100.0f;
    };
}
