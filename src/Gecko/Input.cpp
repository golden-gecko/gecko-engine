#include "Gecko/Camera.hpp"
#include "Gecko/Input.hpp"

Gecko::Input* Ogre::Singleton<Gecko::Input>::msSingleton = nullptr;

namespace Gecko
{
    Input::Input(size_t windowHandle)
    {
        OIS::ParamList pl;

        std::ostringstream ss;
        ss << windowHandle;

        pl.insert(std::make_pair("WINDOW", ss.str()));

        // Set mode to nonexclusive to show mouse.
        pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
        pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));

        // This never returns null.. it will raise an exception on errors
        inputManager = OIS::InputManager::createInputSystem(pl);

        //Lets enable all addons that were compiled in:
        inputManager->enableAddOnFactory(OIS::InputManager::AddOn_All);

        /* TODO: Log this to file
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
        */

        keyboard = dynamic_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
        keyboard->setEventCallback(this);

        mouse = dynamic_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
        mouse->setEventCallback(this);

        // TODO: Set correct size.
        const OIS::MouseState& ms = mouse->getMouseState();

        ms.width = 100;
        ms.height = 100;

        // Create at most 4 joysticks (use old way to create i.e. disregard vendor).
        int numSticks = std::min(inputManager->getNumberOfDevices(OIS::OISJoyStick), static_cast<int>(joysticks.size()));
        for (int i = 0; i < numSticks; ++i)
        {
            joysticks[i] = dynamic_cast<OIS::JoyStick*>(inputManager->createInputObject(OIS::OISJoyStick, true));
            joysticks[i]->setEventCallback(this);
            
            /* TODO: Log this to file
            std::cout << "\n\nCreating Joystick " << (i + 1)
                << "\n\tAxes: " << joysticks[i]->getNumberOfComponents(OIS_Axis)
                << "\n\tSliders: " << joysticks[i]->getNumberOfComponents(OIS_Slider)
                << "\n\tPOV/HATs: " << joysticks[i]->getNumberOfComponents(OIS_POV)
                << "\n\tButtons: " << joysticks[i]->getNumberOfComponents(OIS_Button)
                << "\n\tVector3: " << joysticks[i]->getNumberOfComponents(OIS_Vector3);
            */
        }
    }

    Input::~Input()
    {
        OIS::InputManager::destroyInputSystem(inputManager);
    }

    void Input::capture() const
    {
        if (keyboard)
        {
            keyboard->capture();
        }
        
        if (mouse)
        {
            mouse->capture();
        }

        for (OIS::JoyStick* joystick : joysticks)
        {
            if (joystick)
            {
                joystick->capture();
            }
        }
    }

    bool Input::isKeyDown(OIS::KeyCode key) const
    {
        return keyboard ? keyboard->isKeyDown(key) : false;
    }

    bool Input::keyPressed(const OIS::KeyEvent& arg)
    {
        // std::cout << "keyPressed(" << arg.key << ")" << std::endl;

        if (arg.key == OIS::KeyCode::KC_UP)
        {
        }

        return true;
    }

    bool Input::keyReleased(const OIS::KeyEvent& arg)
    {
        // std::cout << "keyReleased(" << arg.key << ")" << std::endl;

        if (arg.key == OIS::KeyCode::KC_ESCAPE || arg.key == OIS::KeyCode::KC_Q)
        {
        }

        return true;
    }

    bool Input::mouseMoved(const OIS::MouseEvent& arg)
    {
        const OIS::MouseState& s = arg.state;

        /*
        std::cout << "\nMouseMoved: Abs("
            << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
            << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
        */

        Camera::getSingleton().rotate(Ogre::Degree(-arg.state.X.rel * 0.1f), Ogre::Degree(-arg.state.Y.rel * 0.1f));

        return true;
    }

    bool Input::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
    {
        const OIS::MouseState& s = arg.state;

        /*
        std::cout << "\nMouse button #" << id << " pressed. Abs("
            << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
            << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
        */

        return true;
    }

    bool Input::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
    {
        const OIS::MouseState& s = arg.state;

        /*
        std::cout << "\nMouse button #" << id << " released. Abs("
            << s.X.abs << ", " << s.Y.abs << ", " << s.Z.abs << ") Rel("
            << s.X.rel << ", " << s.Y.rel << ", " << s.Z.rel << ")";
        */

        return true;
    }

    bool Input::buttonPressed(const OIS::JoyStickEvent& arg, int button)
    {
        // std::cout << arg.device->vendor() << ". Button Pressed # " << button;

        return true;
    }

    bool Input::buttonReleased(const OIS::JoyStickEvent& arg, int button)
    {
        // std::cout << arg.device->vendor() << ". Button Released # " << button;

        return true;
    }

    bool Input::axisMoved(const OIS::JoyStickEvent& arg, int axis)
    {
        if (arg.state.mAxes[axis].abs > 2500 || arg.state.mAxes[axis].abs < -2500)
        {
            // std::cout << arg.device->vendor() << ". Axis # " << axis << " Value: " << arg.state.mAxes[axis].abs;
        }

        return true;
    }

    bool Input::sliderMoved(const OIS::JoyStickEvent& arg, int index)
    {
        /*
        std::cout
            << arg.device->vendor() << ". Slider # " << index
            << " X Value: " << arg.state.mSliders[index].abX
            << " Y Value: " << arg.state.mSliders[index].abY;
        */

        return true;
    }

    bool Input::povMoved(const OIS::JoyStickEvent& arg, int pov)
    {
        std::cout << arg.device->vendor() << ". POV" << pov << " ";

        if (arg.state.mPOV[pov].direction & OIS::Pov::North)
        {
            // std::cout << "North";
        }
        else if (arg.state.mPOV[pov].direction & OIS::Pov::South)
        {
            // std::cout << "South";
        }

        if (arg.state.mPOV[pov].direction & OIS::Pov::East)
        {
            // std::cout << "East";
        }
        else if (arg.state.mPOV[pov].direction & OIS::Pov::West)
        {
            // std::cout << "West";
        }

        if (arg.state.mPOV[pov].direction == OIS::Pov::Centered)
        {
            // std::cout << "Centered";
        }

        return true;
    }

    bool Input::vector3Moved(const OIS::JoyStickEvent& arg, int index)
    {
        /*
        std::cout
            << arg.device->vendor() << ". Orientation # " << index
            << " X Value: " << arg.state.mVectors[index].x
            << " Y Value: " << arg.state.mVectors[index].y
            << " Z Value: " << arg.state.mVectors[index].z;
        */

        return true;
    }
}
