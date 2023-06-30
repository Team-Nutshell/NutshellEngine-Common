#pragma once
#include "ntshengn_module_interface.h"
#include "../resources/ntshengn_resources_window.h"

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
		virtual WindowID open(int width, int height, const std::string& title) = 0;
		// Returns true if the window with identifier windowID is open, else, returns false
		virtual bool isOpen(WindowID windowID) = 0;
		// Flags the window to be closed at the next update
		virtual void close(WindowID windowID) = 0;

		// Returns the main window identifier
		virtual WindowID getMainWindowID() = 0;
		// Returns the number of opened windows
		virtual uint64_t windowCount() = 0;

		// Changes the size of the window with identifier windowID to width and height
		virtual void setSize(WindowID windowID, int width, int height) = 0;
		// Returns the width of the window with identifier windowID
		virtual int getWidth(WindowID windowID) = 0;
		// Returns the height of the window with identifier windowID
		virtual int getHeight(WindowID windowID) = 0;

		// Changes the position of the window with identifier windowID to x and y
		virtual void setPosition(WindowID windowID, int x, int y) = 0;
		// Returns the horizontal position of the window with identifier windowID
		virtual int getPositionX(WindowID windowID) = 0;
		// Returns the vertical position of the window with identifier windowID
		virtual int getPositionY(WindowID windowID) = 0;

		// If the fullscreen parameter is true, puts the window with identifier windowID in fullscreen, else, puts the window with identifier windowID in windowed
		virtual void setFullscreen(WindowID windowID, bool fullscreen) = 0;
		// Returns true if the window with identifier windowID is in fullscreen mode, else, returns false
		virtual bool isFullscreen(WindowID windowID) = 0;

		// If the borderless parameter is true, puts the window with identifier windowID in borderless, else, adds borders to the window with identifier windowID
		virtual void setBorderless(WindowID windowID, bool borderless) = 0;
		// Returns true if the window with identifier windowID is in borderless mode, else, returns false
		virtual bool isBorderless(WindowID windowID) = 0;

		// If the resizable parameter is true, makes the window with identifier windowID resizable, else, makes the window with identifier windowID not resizable
		virtual void setResizable(WindowID windowID, bool resizable) = 0;
		// Returns true if the window with identifier windowID is resizable, else, returns false
		virtual bool isResizable(WindowID windowID) = 0;

		// Polls events of the windows
		virtual void pollEvents() = 0;

		// Sets the title of the window with identifier windowID
		virtual void setTitle(WindowID windowID, const std::string& title) = 0;

		// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		virtual InputState getKeyState(WindowID windowID, InputKeyboardKey key) = 0;
		// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		virtual InputState getMouseButtonState(WindowID windowID, InputMouseButton mouseButton) = 0;

		// Sets the mouse cursor position
		virtual void setCursorPosition(WindowID windowID, int x, int y) = 0;
		// Gets the mouse cursor horizontal position
		virtual int getCursorPositionX(WindowID windowID) = 0;
		// Gets the mouse cursor vertical position
		virtual int getCursorPositionY(WindowID windowID) = 0;

		// If the mouse cursor is visible in the window with identifier windowID, hides it, else, shows it
		virtual void setCursorVisibility(WindowID windowID, bool visible) = 0;
		// Returns true if the mouse cursor is visible in the window with identifier windowID, else, returns false
		virtual bool isCursorVisible(WindowID windowID) = 0;

		// Returns the native window handle of the window with identifier windowID
		virtual NativeWindowHandle getNativeHandle(WindowID windowID) = 0;
		// Returns the native window additional information of the window with identifier windowID
		virtual NativeWindowAdditionalInformation getNativeAdditionalInformation(WindowID windowID) = 0;
	};

}