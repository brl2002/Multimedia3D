#include "Advanced2d.h"

#ifndef _INPUT_H
#define _INPUT_H 1

namespace Advanced2D {


	//-----------------------------------------------------------------------------
	// XController Class
	//-----------------------------------------------------------------------------
	class XController
	{
	public:
		XController()
			: bConnected(false),
			mThumbLX(0), mThumbLY(0), mThumbRX(0), mThumbRY(0)
		{

		}
		bool isButtonDown(int button);
		bool isButtonReleased(int button);
		bool isButtonPressed(int button);

		int rightTrigger();
		int leftTrigger();
		float rightThumbstickX();
		float rightThumbstickY();
		float leftThumbstickX();
		float leftThumbstickY();
		void setRightVibration(int vibration);
		void setLeftVibration(int vibration);

		void update();

		XINPUT_STATE state; // Stores the state of the controller
		XINPUT_STATE previousState; // Stores the previous state of the controller
		XINPUT_VIBRATION vibration; // Stores the vibration of the controller
		bool bConnected; // Stores the connection status of the controller

	private:
		float mThumbLX; // X value of the left thumbstick
		float mThumbLY; // Y value of the left thumbstick
		float mThumbRX; // X value of the right thumbstick
		float mThumbRY; // Y value of the right thumbstick
	};

    class Input {

    private:
        HWND window; 
        IDirectInput8 *di; 
        IDirectInputDevice8 *keyboard;
        char keyState[256]; 
        IDirectInputDevice8 *mouse; 
        DIMOUSESTATE mouseState; 
        POINT position; 
		XController g_Controllers[XUSER_MAX_COUNT];

    public:
        Input( HWND window );
        virtual ~Input();
        void Update();
        bool GetMouseButton( int button );

        char GetKeyState(int key) { return keyState[key]; }
        long GetPosX() { return position.x; }
        long GetPosY() { return position.y; }
        long GetDeltaX() { return mouseState.lX; }
        long GetDeltaY() { return mouseState.lY; }
        long GetDeltaWheel() { return mouseState.lZ; }

		bool IsControllerConnected(int index) { return g_Controllers[index].bConnected;}
		bool IsButtonPressed(int index, int button) { return g_Controllers[index].isButtonPressed(button); }
		bool IsButtonReleased(int index, int button) { return g_Controllers[index].isButtonReleased(button); }
		bool IsButtonDown(int index, int button) { return g_Controllers[index].isButtonDown(button); }
		bool IsRightTriggerDown(int index) { return g_Controllers[index].state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; }
		bool IsLeftTriggerDown(int index) { return g_Controllers[index].state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD; }
		int GetRightTriggerValue(int index) 
		{ 
			if(IsRightTriggerDown(index))
			{
				return g_Controllers[index].state.Gamepad.bRightTrigger;
			}
			return 0; 
		}
		int GetLeftTriggerValue(int index) 
		{ 
			if(IsLeftTriggerDown(index))
			{
				return g_Controllers[index].state.Gamepad.bLeftTrigger;
			}
			return 0; 
		}
		float GetThumbLX(int index) { return g_Controllers[index].leftThumbstickX(); }
		float GetThumbLY(int index) { return g_Controllers[index].leftThumbstickY(); }
		float GetThumbRX(int index) { return g_Controllers[index].rightThumbstickX(); }
		float GetThumbRY(int index) { return g_Controllers[index].rightThumbstickY(); }
    };

};

#endif
