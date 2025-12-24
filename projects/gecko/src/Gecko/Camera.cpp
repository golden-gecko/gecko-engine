#include "Gecko/PCH.hpp"

#include "Gecko/Camera.hpp"
#include "Gecko/Input.hpp"
#include "Gecko/Scene.hpp"

Gecko::Camera* Ogre::Singleton<Gecko::Camera>::msSingleton = nullptr;

namespace Gecko
{
    Camera::Camera(Scene* scene, const std::string& name) : sceneManager(sceneManager)
    {
        sceneManager = scene->getSceneManager();

        camera = sceneManager->createCamera(name);
        camera->getUserObjectBindings().setUserAny(Ogre::Any(this));
        camera->setNearClipDistance(5.0f);
        camera->setAutoAspectRatio(true);

        sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
        sceneNode->attachObject(camera);
        sceneNode->getUserObjectBindings().setUserAny(Ogre::Any(this));
        sceneNode->setFixedYawAxis(true, Ogre::Vector3f::UNIT_Y);
    }

    Camera::~Camera()
    {
        sceneManager->destroySceneNode(sceneNode);
        sceneManager->destroyCamera(camera);
    }

    Ogre::SceneManager* Camera::getSceneManager() const
    {
        return sceneManager;
    }

    Ogre::Camera* Camera::getCamera() const
    {
        return camera;
    }

    Ogre::SceneNode* Camera::getSceneNode() const
    {
        return sceneNode;
    }

    void Camera::setPosition(const Ogre::Vector3f& position)
    {
        sceneNode->setPosition(position);
    }

    void Camera::setSpeed(float speed)
    {
        this->speed = speed;
    }

    void Camera::lookAt(const Ogre::Vector3f& position)
    {
        sceneNode->lookAt(position, Ogre::Node::TransformSpace::TS_PARENT);
    }

    void Camera::move(const Ogre::Vector3f& position)
    {
        sceneNode->translate(position, Ogre::Node::TransformSpace::TS_LOCAL);
    }

    void Camera::rotate(const Ogre::Degree& yaw, const Ogre::Degree& pitch)
    {
        sceneNode->yaw(yaw, Ogre::Node::TS_WORLD);
        sceneNode->pitch(pitch, Ogre::Node::TS_LOCAL);
    }

    void Camera::update(float time)
    {
        Ogre::Vector3 direction = Ogre::Vector3::ZERO;

        if (Input::getSingleton().isKeyDown(OIS::KC_D))
        {
            direction += Ogre::Vector3::UNIT_X;
        }
        else if (Input::getSingleton().isKeyDown(OIS::KC_A))
        {
            direction += Ogre::Vector3::NEGATIVE_UNIT_X;
        }

        if (Input::getSingleton().isKeyDown(OIS::KC_Q))
        {
            direction += Ogre::Vector3::UNIT_Y;
        }
        else if (Input::getSingleton().isKeyDown(OIS::KC_Z))
        {
            direction += Ogre::Vector3::NEGATIVE_UNIT_Y;
        }

        if (Input::getSingleton().isKeyDown(OIS::KC_S))
        {
            direction += Ogre::Vector3::UNIT_Z;
        }
        else if (Input::getSingleton().isKeyDown(OIS::KC_W))
        {
            direction += Ogre::Vector3::NEGATIVE_UNIT_Z;
        }

        move(direction * speed * time);
    }
}
