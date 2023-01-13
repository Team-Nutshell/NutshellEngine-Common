#pragma once
#include "ntsh_module_interface.h"
#include "../resources/ntsh_resources_window.h"
#include "../utils/ntsh_engine_input_enums.h"
#if defined(NTSH_OS_WINDOWS)
#include <windows.h>
#elif defined(NTSH_OS_LINUX)
#include <X11/Xlib.h>
#endif

#define NTSH_MAIN_WINDOW 0

class NutshellWindowModuleInterface : public NutshellModuleInterface {
public:
	NutshellWindowModuleInterface() {}
	NutshellWindowModuleInterface(const std::string& name) : NutshellModuleInterface(Ntsh::ModuleType::Window, name) {}
	virtual ~NutshellWindowModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;

	// Opens a new window and returns a unique identifier
	virtual Ntsh::WindowId open(int width, int height, const std::string& title) = 0;
	// Returns true if the window with identifier windowId is open, else, returns false
	virtual bool isOpen(Ntsh::WindowId windowId) = 0;
	// Flags the window to be closed at the next update
	virtual void close(Ntsh::WindowId windowId) = 0;

	// Returns the number of opened windows
	virtual uint64_t windowCount() = 0;

	// Changes the size of the window with identifier windowId to width and height
	virtual void setSize(Ntsh::WindowId windowId, int width, int height) = 0;
	// Returns the width of the window with identifier windowId
	virtual int getWidth(Ntsh::WindowId windowId) = 0;
	// Returns the height of the window with identifier windowId
	virtual int getHeight(Ntsh::WindowId windowId) = 0;

	// Changes the position of the window with identifier windowId to x and y
	virtual void setPosition(Ntsh::WindowId windowId, int x, int y) = 0;
	// Returns the horizontal position of the window with identifier windowId
	virtual int getPositionX(Ntsh::WindowId windowId) = 0;
	// Returns the vertical position of the window with identifier windowId
	virtual int getPositionY(Ntsh::WindowId windowId) = 0;

	// If the fullscreen parameter is true, puts the window with identifier windowId in fullscreen, else, puts the window with identifier windowId in windowed
	virtual void setFullscreen(Ntsh::WindowId windowId, bool fullscreen) = 0;
	// Returns true if the window with identifier windowId is in fullscreen mode, else, returns false
	virtual bool isFullscreen(Ntsh::WindowId windowId) = 0;

	// Polls events of the windows
	virtual void pollEvents() = 0;

	// Sets the title of the window with identifier windowId
	virtual void setTitle(Ntsh::WindowId windowId, const std::string& title) = 0;

	// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	virtual NtshInputState getKeyState(Ntsh::WindowId windowId, NtshInputKeyboardKey key) = 0;
	// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	virtual NtshInputState getMouseButtonState(Ntsh::WindowId windowId, NtshInputMouseButton mouseButton) = 0;

	// Sets the mouse cursor position
	virtual void setCursorPosition(Ntsh::WindowId windowId, int x, int y) = 0;
	// Gets the mouse cursor horizontal position
	virtual int getCursorPositionX(Ntsh::WindowId windowId) = 0;
	// Gets the mouse cursor vertical position
	virtual int getCursorPositionY(Ntsh::WindowId windowId) = 0;

	// If the mouse cursor is visible in the window with identifier windowId, hides it, else, shows it
	virtual void setCursorVisibility(Ntsh::WindowId windowId, bool visible) = 0;
	// Returns true if the mouse cursor is visible in the window with identifier windowId, else, returns false
	virtual bool isCursorVisible(Ntsh::WindowId windowId) = 0;

#if defined(NTSH_OS_WINDOWS)
	// Returns the native Win32 window handle of the window with identifier windowId
	virtual HWND getNativeHandle(Ntsh::WindowId windowId) = 0;
#elif defined(NTSH_OS_LINUX)
	// Returns the native X window handle of the window with identifier windowId
	virtual Window getNativeHandle(Ntsh::WindowId windowId) = 0;
#endif
};