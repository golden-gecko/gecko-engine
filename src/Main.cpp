#include "PCH.hpp"

#include "App.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "Input.hpp"
#include "Light.hpp"
#include "Scene.hpp"

int main()
{
    // Create app.
    std::unique_ptr<Gecko::App> app = std::make_unique<Gecko::App>();
    std::unique_ptr<Gecko::Input> input = std::make_unique<Gecko::Input>(app->getRenderWindowHandle());

    // Create scene.
    std::shared_ptr<Gecko::Scene> scene = std::make_shared<Gecko::Scene>(app->getRoot());

    // Add objects to scene.
    std::shared_ptr<Gecko::Light> light = std::make_shared<Gecko::Light>(scene, "Light");
    std::shared_ptr<Gecko::Camera> camera = std::make_shared<Gecko::Camera>(scene, "Camera");
    std::shared_ptr<Gecko::GameObject> gameObject = std::make_shared<Gecko::GameObject>(scene, "robot.mesh");

    // Setup objects.
    camera->setPosition(Ogre::Vector3f(0.0f, 140.0f, 140.0f));
    camera->lookAt(Ogre::Vector3::ZERO);

    // Run app.
    app->setCamera(camera);
    app->run();
    
	return 0;
}
