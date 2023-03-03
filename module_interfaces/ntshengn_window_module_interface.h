#pragma once
#include "ntshengn_module_interface.h"
#include "../resources/ntshengn_resources_window.h"
#if defined(NTSHENGN_OS_WINDOWS)
#include <windows.h>
#elif defined(NTSHENGN_OS_LINUX)
#include <X11/Xlib.h>
#undef None
#undef Success
#endif

#define NTSHENGN_MAIN_WINDOW 0

namespace NtshEngn {

	class WindowModuleInterface : public ModuleInterface {
	public:
		WindowModuleInterface() {}
		WindowModuleInterface(const std::string& name) : ModuleInterface(ModuleType::Window, name) {}
		virtual ~WindowModuleInterface() {}

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		// Opens a new window and returns a unique identifier
		virtual WindowId open(int width, int height, const std::string& title) = 0;
		// Returns true if the window with identifier windowId is open, else, returns false
		virtual bool isOpen(WindowId windowId) = 0;
		// Flags the window to be closed at the next update
		virtual void close(WindowId windowId) = 0;

		// Returns the number of opened windows
		virtual uint64_t windowCount() = 0;

		// Changes the size of the window with identifier windowId to width and height
		virtual void setSize(WindowId windowId, int width, int height) = 0;
		// Returns the width of the window with identifier windowId
		virtual int getWidth(WindowId windowId) = 0;
		// Returns the height of the window with identifier windowId
		virtual int getHeight(WindowId windowId) = 0;

		// Changes the position of the window with identifier windowId to x and y
		virtual void setPosition(WindowId windowId, int x, int y) = 0;
		// Returns the horizontal position of the window with identifier windowId
		virtual int getPositionX(WindowId windowId) = 0;
		// Returns the vertical position of the window with identifier windowId
		virtual int getPositionY(WindowId windowId) = 0;

		// If the fullscreen parameter is true, puts the window with identifier windowId in fullscreen, else, puts the window with identifier windowId in windowed
		virtual void setFullscreen(WindowId windowId, bool fullscreen) = 0;
		// Returns true if the window with identifier windowId is in fullscreen mode, else, returns false
		virtual bool isFullscreen(WindowId windowId) = 0;

		// Polls events of the windows
		virtual void pollEvents() = 0;

		// Sets the title of the window with identifier windowId
		virtual void setTitle(WindowId windowId, const std::string& title) = 0;

		// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		virtual InputState getKeyState(WindowId windowId, InputKeyboardKey key) = 0;
		// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		virtual InputState getMouseButtonState(WindowId windowId, InputMouseButton mouseButton) = 0;

		// Sets the mouse cursor position
		virtual void setCursorPosition(WindowId windowId, int x, int y) = 0;
		// Gets the mouse cursor horizontal position
		virtual int getCursorPositionX(WindowId windowId) = 0;
		// Gets the mouse cursor vertical position
		virtual int getCursorPositionY(WindowId windowId) = 0;

		// If the mouse cursor is visible in the window with identifier windowId, hides it, else, shows it
		virtual void setCursorVisibility(WindowId windowId, bool visible) = 0;
		// Returns true if the mouse cursor is visible in the window with identifier windowId, else, returns false
		virtual bool isCursorVisible(WindowId windowId) = 0;

	#if defined(NTSHENGN_OS_WINDOWS)
		// Returns the native Win32 window handle of the window with identifier windowId
		virtual HWND getNativeHandle(WindowId windowId) = 0;
	#elif defined(NTSHENGN_OS_LINUX)
		// Returns the native X window handle of the window with identifier windowId
		virtual Window getNativeHandle(WindowId windowId) = 0;
	#endif
	};

}