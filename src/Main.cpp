#include "PCH.hpp"

namespace Gecko
{
    class Camera
    {
    public:
        Camera(Ogre::SceneManager* sceneManager, const std::string& name) : sceneManager(sceneManager)
        {
            camera = sceneManager->createCamera(name);
            camera->setNearClipDistance(5.0f);
            camera->setAutoAspectRatio(true);

            sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
            sceneNode->attachObject(camera);
        }

        ~Camera()
        {
            sceneManager->destroySceneNode(sceneNode);
            sceneManager->destroyCamera(camera);
        }

        Ogre::Camera* getCamera() const
        {
            return camera;
        }

        Ogre::SceneNode* getSceneNode() const
        {
            return sceneNode;
        }

    protected:
        Ogre::SceneManager* sceneManager;
        Ogre::Camera* camera;
        Ogre::SceneNode* sceneNode;
    };

    class GameObject
    {
    public:
        GameObject(Ogre::SceneManager* sceneManager, const std::string& name) : sceneManager(sceneManager)
        {
            entity = sceneManager->createEntity(name);

            sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
            sceneNode->attachObject(entity);
        }

        ~GameObject()
        {
            sceneManager->destroySceneNode(sceneNode);
            sceneManager->destroyEntity(entity);
        }

        Ogre::Entity* getEntity() const
        {
            return entity;
        }

        Ogre::SceneNode* getSceneNode() const
        {
            return sceneNode;
        }

    protected:
        Ogre::SceneManager* sceneManager;
        Ogre::Entity* entity;
        Ogre::SceneNode* sceneNode;
    };

    class Input : public Ogre::Singleton<Input>, public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
    {
    public:
        Input(size_t windowHandle)
        {
            using namespace OIS;

            ParamList pl;

            /*
            //Create a capture window for Input Grabbing
            hWnd = CreateDialog(nullptr, MAKEINTRESOURCE(IDD_DIALOG1), nullptr, (DLGPROC)DlgProc);
            if (hWnd == nullptr)
                OIS_EXCEPT(E_General, "Failed to create Win32 Window Dialog!");

            ShowWindow(hWnd, SW_SHOW);
            */

            std::ostringstream wnd;
            wnd << (size_t)windowHandle;

            pl.insert(std::make_pair(std::string("WINDOW"), wnd.str()));

            //Default mode is foreground exclusive..but, we want to show mouse - so nonexclusive
            pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
            pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

            //This never returns null.. it will raise an exception on errors
            inputManager = InputManager::createInputSystem(pl);

            //Lets enable all addons that were compiled in:
            inputManager->enableAddOnFactory(InputManager::AddOn_All);

            //Print debugging information
            unsigned int v = inputManager->getVersionNumber();
            std::cout << "OIS Version: " << (v >> 16) << "." << ((v >> 8) & 0x000000FF) << "." << (v & 0x000000FF)
                << "\nRelease Name: " << inputManager->getVersionName()
                << "\nManager: " << inputManager->inputSystemName()
                << "\nTotal Keyboards: " << inputManager->getNumberOfDevices(OISKeyboard)
                << "\nTotal Mice: " << inputManager->getNumberOfDevices(OISMouse)
                << "\nTotal JoySticks: " << inputManager->getNumberOfDevices(OISJoyStick);

            //List all devices
            const char* g_DeviceType[6] = { "OISUnknown", "OISKeyboard", "OISMouse", "OISJoyStick", "OISTablet", "OISOther" };
            DeviceList list = inputManager->listFreeDevices();
            for (DeviceList::iterator i = list.begin(); i != list.end(); ++i)
                std::cout << "\n\tDevice: " << g_DeviceType[i->first] << " Vendor: " << i->second;

            keyboard = (Keyboard*)inputManager->createInputObject(OISKeyboard, true);
            keyboard->setEventCallback(this);

            mouse = (Mouse*)inputManager->createInputObject(OISMouse, true);
            mouse->setEventCallback(this);
            const MouseState& ms = mouse->getMouseState();
            ms.width = 100;
            ms.height = 100;

            //This demo uses at most 4 joysticks - use old way to create (i.e. disregard vendor)
            int numSticks = std::min(inputManager->getNumberOfDevices(OISJoyStick), static_cast<int>(joysticks.size()));
            for (int i = 0; i < numSticks; ++i)
            {
                joysticks[i] = (JoyStick*)inputManager->createInputObject(OISJoyStick, true);
                joysticks[i]->setEventCallback(this);
                std::cout << "\n\nCreating Joystick " << (i + 1)
                    << "\n\tAxes: " << joysticks[i]->getNumberOfComponents(OIS_Axis)
                    << "\n\tSliders: " << joysticks[i]->getNumberOfComponents(OIS_Slider)
                    << "\n\tPOV/HATs: " << joysticks[i]->getNumberOfComponents(OIS_POV)
                    << "\n\tButtons: " << joysticks[i]->getNumberOfComponents(OIS_Button)
                    << "\n\tVector3: " << joysticks[i]->getNumberOfComponents(OIS_Vector3);
            }
        }

        void capture() const
        {
            keyboard->capture();
            mouse->capture();

            for (OIS::JoyStick* joystick : joysticks)
            {
                if (joystick)
                {
                    joystick->capture();
                }
            }
        }

        bool isKeyDown(OIS::KeyCode key) const
        {
            return keyboard->isKeyDown(key);
        }

        bool keyPressed(const OIS::KeyEvent& arg) override
        {
            std::cout << "keyPressed(" << arg.key << ")" << std::endl;

            if (arg.key == OIS::KeyCode::KC_UP)
            {
            }

            return true;
        }

        bool keyReleased(const OIS::KeyEvent& arg) override
        {
            std::cout << "keyReleased(" << arg.key << ")" << std::endl;

            if (arg.key == OIS::KeyCode::KC_ESCAPE || arg.key == OIS::KeyCode::KC_Q)
            {
            }

            return true;
        }

        bool mouseMoved(const OIS::MouseEvent& arg) override
        {
            const OIS::MouseState& s = arg.state;

            std::cout << "\nMouseMoved: Abs("
                << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
                << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";

            return true;
        }

        bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) override
        {
            const OIS::MouseState& s = arg.state;

            std::cout << "\nMouse button #" << id << " pressed. Abs("
                << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
                << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";

            return true;
        }

        bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) override
        {
            const OIS::MouseState& s = arg.state;

            std::cout << "\nMouse button #" << id << " released. Abs("
                << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
                << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";

            return true;
        }

        bool buttonPressed(const OIS::JoyStickEvent& arg, int button) override
        {
            std::cout << arg.device->vendor() << ". Button Pressed # " << button;

            return true;
        }

        bool buttonReleased(const OIS::JoyStickEvent& arg, int button) override
        {
            std::cout << arg.device->vendor() << ". Button Released # " << button;

            return true;
        }

        bool axisMoved(const OIS::JoyStickEvent& arg, int axis) override
        {
            if (arg.state.mAxes[axis].abs > 2500 || arg.state.mAxes[axis].abs < -2500)
            {
                std::cout << arg.device->vendor() << ". Axis # " << axis << " Value: " << arg.state.mAxes[axis].abs;
            }

            return true;
        }

        bool sliderMoved(const OIS::JoyStickEvent& arg, int index) override
        {
            std::cout
                << arg.device->vendor() << ". Slider # " << index
                << " X Value: " << arg.state.mSliders[index].abX
                << " Y Value: " << arg.state.mSliders[index].abY;

            return true;
        }

        bool povMoved(const OIS::JoyStickEvent& arg, int pov) override
        {
            std::cout << arg.device->vendor() << ". POV" << pov << " ";

            if (arg.state.mPOV[pov].direction & OIS::Pov::North)
            {
                std::cout << "North";
            }
            else if (arg.state.mPOV[pov].direction & OIS::Pov::South)
            {
                std::cout << "South";
            }

            if (arg.state.mPOV[pov].direction & OIS::Pov::East)
            {
                std::cout << "East";
            }
            else if (arg.state.mPOV[pov].direction & OIS::Pov::West)
            {
                std::cout << "West";
            }

            if (arg.state.mPOV[pov].direction == OIS::Pov::Centered)
            {
                std::cout << "Centered";
            }

            return true;
        }

        bool vector3Moved(const OIS::JoyStickEvent& arg, int index) override
        {
            std::cout
                << arg.device->vendor() << ". Orientation # " << index
                << " X Value: " << arg.state.mVectors[index].x
                << " Y Value: " << arg.state.mVectors[index].y
                << " Z Value: " << arg.state.mVectors[index].z;

            return true;
        }

    protected:
        OIS::InputManager* inputManager = nullptr;
        OIS::Keyboard* keyboard = nullptr;
        OIS::Mouse* mouse = nullptr;
        std::array<OIS::JoyStick*, 4> joysticks = { nullptr, nullptr, nullptr, nullptr };
    };

    class Light
    {
    public:
        Light(Ogre::SceneManager* sceneManager, const std::string& name) : sceneManager(sceneManager)
        {
            light = sceneManager->createLight(name);
            light->setCastShadows(false);
            light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);

            sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
            sceneNode->attachObject(light);
            sceneNode->lookAt(Ogre::Vector3f(-1.0f, -1.0f, -1.0f), Ogre::Node::TransformSpace::TS_PARENT);
        }

        ~Light()
        {
            sceneManager->destroySceneNode(sceneNode);
            sceneManager->destroyLight(light);
        }

    protected:
        Ogre::SceneManager* sceneManager;
        Ogre::Light* light;
        Ogre::SceneNode* sceneNode;
    };

    class Scene
    {
    public:
        Scene(Ogre::SceneManager* sceneManager) : sceneManager(sceneManager)
        {
        }

    protected:
        Ogre::SceneManager* sceneManager;
    };

    class App : public Ogre::Singleton<App>, public Ogre::FrameListener
    {
    public:
        App()
        {
            ctx = std::make_shared<OgreBites::ApplicationContext>();
            ctx->initApp();

            if (ctx->getRoot()->restoreConfig() == false)
            {
                ctx->getRoot()->showConfigDialog(OgreBites::getNativeConfigDialog());
            }

            ctx->getRoot()->addFrameListener(this);
        }

        ~App()
        {
            ctx->closeApp();
        }

        void run()
        {
            ctx->getRoot()->startRendering();
        }

        bool frameStarted(const Ogre::FrameEvent& evt) override
        {
            Input::getSingleton().capture();

            if (Input::getSingleton().isKeyDown(OIS::KeyCode::KC_ESCAPE))
            {
                return false;
            }

            return true;
        }

        std::shared_ptr<OgreBites::ApplicationContext> getContext() const
        {
            return ctx;
        }

        void setCamera(Ogre::Camera* camera)
        {
            ctx->getRenderWindow()->addViewport(camera)->setBackgroundColour(Ogre::ColourValue::White);
        }

    protected:
        std::shared_ptr<OgreBites::ApplicationContext> ctx;
    };
}

Gecko::App* Ogre::Singleton<Gecko::App>::msSingleton = nullptr;
Gecko::Input* Ogre::Singleton<Gecko::Input>::msSingleton = nullptr;

int main()
{
    std::unique_ptr<Gecko::App> app = std::make_unique<Gecko::App>();

    size_t windowHadle = 0;
    app->getContext()->getRenderWindow()->getCustomAttribute("WINDOW", &windowHadle);

    std::unique_ptr<Gecko::Input> input = std::make_unique<Gecko::Input>(windowHadle);

    Ogre::Root* root = app->getContext()->getRoot();
    Ogre::SceneManager* sceneManager = root->createSceneManager();

    Ogre::RTShader::ShaderGenerator::getSingletonPtr()->addSceneManager(sceneManager);

    std::shared_ptr light = std::make_shared<Gecko::Light>(sceneManager, "MainLight");
    std::shared_ptr camera = std::make_shared<Gecko::Camera>(sceneManager, "Camera");
    std::shared_ptr gameObject = std::make_shared<Gecko::GameObject>(sceneManager, "robot.mesh");

    camera->getSceneNode()->setPosition(40.0f, 40.0f, 40.0f);
    camera->getSceneNode()->lookAt(Ogre::Vector3::ZERO, Ogre::Node::TransformSpace::TS_PARENT);

    gameObject->getSceneNode()->setScale(Ogre::Vector3f::UNIT_SCALE * 0.2f);

    app->setCamera(camera->getCamera());
    app->run();
    
	return 0;
}
