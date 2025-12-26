#pragma once

#include "Gecko/Gecko.hpp"

namespace Gecko
{
    class Scene;

    class Camera : public Ogre::Singleton<Camera>
    {
    public:
        Camera(Scene* scene, const std::string& name);

        virtual ~Camera();

        void lookAt(const Ogre::Vector3f& position);
        void move(const Ogre::Vector3f& position);
        void rotate(const Ogre::Degree& yaw, const Ogre::Degree& pitch);

        void update(float time);

        Ogre::SceneManager* getSceneManager() const;
        Ogre::Camera* getCamera() const;
        Ogre::SceneNode* getSceneNode() const;

        void setPosition(const Ogre::Vector3f& position);
        void setSpeed(float speed);

    protected:
        Ogre::SceneManager* sceneManager = nullptr;
        Ogre::Camera* camera = nullptr;
        Ogre::SceneNode* sceneNode = nullptr;

        float speed = 100.0f;
    };
}
