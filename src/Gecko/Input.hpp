#pragma once

#include "Gecko/Gecko.hpp"

namespace Gecko
{
    class Input : public Ogre::Singleton<Input>, public OIS::KeyListener, public OIS::MouseListener, public OIS::JoyStickListener
    {
    public:
        // OIS::KeyListener
        bool keyPressed(const OIS::KeyEvent& arg) override;
        bool keyReleased(const OIS::KeyEvent& arg) override;

        // OIS::MouseListener
        bool mouseMoved(const OIS::MouseEvent& arg) override;
        bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) override;
        bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) override;

        // OIS::JoyStickListener
        bool buttonPressed(const OIS::JoyStickEvent& arg, int button) override;
        bool buttonReleased(const OIS::JoyStickEvent& arg, int button) override;
        bool axisMoved(const OIS::JoyStickEvent& arg, int axis) override;
        bool sliderMoved(const OIS::JoyStickEvent& arg, int index) override;
        bool povMoved(const OIS::JoyStickEvent& arg, int pov) override;
        bool vector3Moved(const OIS::JoyStickEvent& arg, int index) override;

    public:
        Input(size_t windowHandle);

        virtual ~Input();

        void capture() const;

        bool isKeyDown(OIS::KeyCode key) const;

    protected:
        OIS::InputManager* inputManager = nullptr;
        OIS::Keyboard* keyboard = nullptr;
        OIS::Mouse* mouse = nullptr;
        std::array<OIS::JoyStick*, 4> joysticks = { nullptr, nullptr, nullptr, nullptr };
    };
}
