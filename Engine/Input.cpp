#include "Advanced2D.h"

namespace Advanced2D {

	//-----------------------------------------------------------------------------
	// Updates the state of the controller
	//-----------------------------------------------------------------------------
	void XController::update()
	{
		if( (state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) && 
			(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ) 
		{   
			mThumbLX = 0;
			mThumbLY = 0;
		}
		else
		{
			mThumbLX = state.Gamepad.sThumbLX;
			mThumbLY = state.Gamepad.sThumbLY;
		}
		if( (state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) && 
			(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ) 
		{   
			mThumbRX = 0;
			mThumbRY = 0;
		}
		else
		{
			mThumbRX = state.Gamepad.sThumbRX;
			mThumbRY = state.Gamepad.sThumbRY;
		}
	}

	//-----------------------------------------------------------------------------
	// Checks to see if a button is pressed down
	//-----------------------------------------------------------------------------
	bool XController::isButtonDown(int button)
	{
		if( bConnected )
		{
			WORD wButtons = state.Gamepad.wButtons;
			if (wButtons & button)
			{	
				return true;
			}
		}
		return false;
	}

	//-----------------------------------------------------------------------------
	// Checks to see if a button is released
	//-----------------------------------------------------------------------------
	bool XController::isButtonReleased(int button)
	{
		if( bConnected )
		{
			WORD wButtons = state.Gamepad.wButtons;
			WORD wPrevButtons = previousState.Gamepad.wButtons;
			if (wPrevButtons & button && !(wButtons & button))
			{	
				return true;
			}
		}
		return false;
	}

	//-----------------------------------------------------------------------------
	// Checks to see if a button is pressed
	//-----------------------------------------------------------------------------
	bool XController::isButtonPressed(int button)
	{
		if( bConnected )
		{
			WORD wButtons = state.Gamepad.wButtons;
			WORD wPrevButtons = previousState.Gamepad.wButtons;
			if (!(wPrevButtons & button) && wButtons & button)
			{	
				return true;
			}
		}
		return false;
	}

	//-----------------------------------------------------------------------------
	// Returns the right trigger value
	//-----------------------------------------------------------------------------
	int XController::rightTrigger()
	{
		if( bConnected )
		{
			return state.Gamepad.bRightTrigger;
		}
		return 0;
	}

	//-----------------------------------------------------------------------------
	// Returns the left trigger value
	//-----------------------------------------------------------------------------
	int XController::leftTrigger()
	{
		return state.Gamepad.bLeftTrigger;
	}

	//-----------------------------------------------------------------------------
	// Returns the right thumbstick value in the X direction
	//-----------------------------------------------------------------------------
	float XController::rightThumbstickX()
	{
		return mThumbRX;
	}

	//-----------------------------------------------------------------------------
	// Returns the right thumbstick value in the Y direction
	//-----------------------------------------------------------------------------
	float XController::rightThumbstickY()
	{
		return mThumbRY*(-1);
	}

	//-----------------------------------------------------------------------------
	// Returns the left thumbstick value in the X direction
	//-----------------------------------------------------------------------------
	float XController::leftThumbstickX()
	{
		return mThumbLX;
	}

	//-----------------------------------------------------------------------------
	// Returns the left thumbstick value in the Y direction
	//-----------------------------------------------------------------------------
	float XController::leftThumbstickY()
	{
		return mThumbLY*(-1);
	}

	//-----------------------------------------------------------------------------
	// Sets the vibration of the right motor
	//-----------------------------------------------------------------------------
	void XController::setRightVibration(int v)
	{
		if (v >= 0 && v <= 65535)
			vibration.wRightMotorSpeed = v;
	}

	//-----------------------------------------------------------------------------
	// Sets the vibration of the left motor
	//-----------------------------------------------------------------------------
	void XController::setLeftVibration(int v)
	{
		if (v >= 0 && v <= 65535)
			vibration.wLeftMotorSpeed = v;
	}

    Input::Input( HWND hwnd )
    {
        //save window handle
        window = hwnd;
    
        //create DirectInput object
        DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
            IID_IDirectInput8, (void**)&di, NULL );
    
        //initialize keyboard
        di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
        keyboard->SetDataFormat( &c_dfDIKeyboard );
        keyboard->SetCooperativeLevel( window, 
            DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
        keyboard->Acquire();
    
        //initialize mouse
        di->CreateDevice(GUID_SysMouse, &mouse, NULL);
        mouse->SetDataFormat(&c_dfDIMouse);
        mouse->SetCooperativeLevel(window,DISCL_FOREGROUND|DISCL_NONEXCLUSIVE);
        mouse->Acquire();
    }
    
    Input::~Input()
    {
        di->Release();
        keyboard->Release();
        mouse->Release();
    }
    
    void Input::Update()
    {
        //poll state of the keyboard
        keyboard->Poll();
        if (!SUCCEEDED(keyboard->GetDeviceState(256,(LPVOID)&keyState)))
        {
            //keyboard device lost, try to re-acquire
            keyboard->Acquire();
        }

        //poll state of the mouse
        mouse->Poll();
        if (!SUCCEEDED(mouse->GetDeviceState(sizeof(DIMOUSESTATE),&mouseState)))
        {
            //mouse device lose, try to re-acquire
            mouse->Acquire();
        }
    
        //get mouse position on screen
        GetCursorPos(&position);
        ScreenToClient(window, &position);
    
    }
    
    bool Input::GetMouseButton( int button )
    {
        return ( mouseState.rgbButtons[button] & 0x80 );
    }
    
};
