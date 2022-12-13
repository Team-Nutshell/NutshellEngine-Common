#pragma once
#include "ntsh_module_interface.h"
#include "../utils/ntsh_engine_input_enums.h"
#ifdef NTSH_OS_WINDOWS
#include <windows.h>
#elif NTSH_OS_LINUX
#include <X11/Xlib.h>
#endif

class NutshellWindowModuleInterface : public NutshellModuleInterface {
protected:
public:
	NutshellWindowModuleInterface() {}
	NutshellWindowModuleInterface(const std::string& name) : NutshellModuleInterface(NtshModuleType::Window, name) {}
	virtual ~NutshellWindowModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;

	// Sends a request to close the window
	virtual void close() = 0;
	// Returns true if there has been a request to close the window, else, returns false
	virtual bool shouldClose() = 0;

	// Changes the size of the window to width and height
	virtual void setSize(int width, int height) = 0;
	// Returns the width of the window
	virtual int getWidth() = 0;
	// Returns the height of the window
	virtual int getHeight() = 0;

	// Returns true if the window is in fullscreen mode, else, returns false
	virtual bool isFullscreen() = 0;
	// If the fullscreen parameter is true, puts the window in fullscreen, else, puts the window in windowed
	virtual void setFullscreen(bool fullscreen) = 0;

	// Polls events
	virtual void pollEvents() = 0;

	// Sets the title of the window
	virtual void setTitle(const std::string& title) = 0;

	// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	virtual NtshInputState getKeyState(NtshInputKeyboardKey key) = 0;
	// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	virtual NtshInputState getButtonState(NtshInputMouseButton button) = 0;

	// Sets the mouse position
	virtual void setMousePosition(int x, int y) = 0;
	// Gets the mouse horizontal position
	virtual int getMouseXPosition() = 0;
	// Gets the mouse vertical position
	virtual int getMouseYPosition() = 0;

#ifdef NTSH_OS_WINDOWS
	// Returns the native Win32 window handle
	virtual HWND getNativeHandle() = 0;
#elif NTSH_OS_LINUX
	// Returns the native X window handle
	virtual Window getNativeHandle() = 0;
#endif
};