#pragma once
#include "ntsh_module_interface.h"
#include "../utils/ntsh_engine_input_enums.h"
#if defined(NTSH_OS_WINDOWS)
#include <windows.h>
#elif defined(NTSH_OS_LINUX)
#include <X11/Xlib.h>
#endif

typedef uint64_t NtshWindowId;

#define NTSH_MAIN_WINDOW 0

class NutshellWindowModuleInterface : public NutshellModuleInterface {
public:
	NutshellWindowModuleInterface() {}
	NutshellWindowModuleInterface(const std::string& name) : NutshellModuleInterface(NtshModuleType::Window, name) {}
	virtual ~NutshellWindowModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;

	// Opens a new window and returns a unique identifier
	virtual NtshWindowId open() = 0;
	// Sends a request to close the window with identifier windowId
	virtual void close(NtshWindowId windowId) = 0;
	// Returns true if there has been a request to close the window with identifier windowId, else, returns false
	virtual bool shouldClose(NtshWindowId windowId) = 0;

	// Returns the number of opened windows
	virtual uint64_t windowCount() = 0;

	// Changes the size of the window with identifier windowId to width and height
	virtual void setSize(NtshWindowId windowId, int width, int height) = 0;
	// Returns the width of the window with identifier windowId
	virtual int getWidth(NtshWindowId windowId) = 0;
	// Returns the height of the window with identifier windowId
	virtual int getHeight(NtshWindowId windowId) = 0;

	// Changes the position of the window with identifier windowId to x and y
	virtual void setPosition(NtshWindowId windowId, int x, int y) = 0;
	// Returns the horizontal position of the window with identifier windowId
	virtual int getPositionX(NtshWindowId windowId) = 0;
	// Returns the vertical position of the window with identifier windowId
	virtual int getPositionY(NtshWindowId windowId) = 0;

	// Returns true if the window with identifier windowId is in fullscreen mode, else, returns false
	virtual bool isFullscreen(NtshWindowId windowId) = 0;
	// If the fullscreen parameter is true, puts the window with identifier windowId in fullscreen, else, puts the window with identifier windowId in windowed
	virtual void setFullscreen(NtshWindowId windowId, bool fullscreen) = 0;

	// Polls events of the window with identifier windowId
	virtual void pollEvents(NtshWindowId windowId) = 0;

	// Sets the title of the window with identifier windowId
	virtual void setTitle(NtshWindowId windowId, const std::string& title) = 0;

	// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	virtual NtshInputState getKeyState(NtshWindowId windowId, NtshInputKeyboardKey key) = 0;
	// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	virtual NtshInputState getButtonState(NtshWindowId windowId, NtshInputMouseButton button) = 0;

	// Sets the mouse cursor position
	virtual void setCursorPosition(NtshWindowId windowId, int x, int y) = 0;
	// Gets the mouse cursor horizontal position
	virtual int getCursorXPosition(NtshWindowId windowId) = 0;
	// Gets the mouse cursor vertical position
	virtual int getCursorYPosition(NtshWindowId windowId) = 0;

	// Returns true if the mouse cursor is visible in the window with identifier windowId, else, returns false
	virtual bool isCursorVisible(NtshWindowId windowId) = 0;
	// If the mouse cursor is visible in the window with identifier windowId, hides it, else, shows it
	virtual void setCursorVisibility(NtshWindowId windowId, bool visible) = 0;

#if defined(NTSH_OS_WINDOWS)
	// Returns the native Win32 window handle
	virtual HWND getNativeHandle() = 0;
#elif defined(NTSH_OS_LINUX)
	// Returns the native X window handle
	virtual Window getNativeHandle() = 0;
#endif
};