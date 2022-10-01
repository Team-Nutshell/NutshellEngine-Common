#pragma once
#include "ntsh_module_interface.h"

class NutshellWindowModuleInterface : public NutshellModuleInterface {
protected:
public:
	NutshellWindowModuleInterface() {}
	NutshellWindowModuleInterface(const std::string& name) : NutshellModuleInterface(NTSH_MODULE_WINDOW, name) {}
	virtual ~NutshellWindowModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;

	// Send a request to close the window
	virtual void closeWindow() = 0;
	// Returns true if there has been a request to close the window, else if there has been no request to close the window
	virtual bool shouldClose() = 0;

	// Changes the size of the window to width and height
	virtual void setWindowSize(int width, int height) = 0;
	// Returns the width of the window
	virtual int getWindowWidth() = 0;
	// Returns the height of the window
	virtual int getWindowHeight() = 0;

	// Returns true if the window is in fullscreen mode, else, return false
	virtual bool isFullscreen() = 0;
	// If the fullscreen parameter is true, puts the window in fullscreen, else, puts the window in windowed
	virtual void setFullscreen(bool fullscreen) = 0;

	// Sets the title of the window
	virtual void setTitle(const std::string& title) = 0;
};

#ifdef NTSH_OS_WINDOWS
typedef NutshellWindowModuleInterface* (__stdcall *createWindowModule_t)();
typedef void (__stdcall *destroyWindowModule_t)(NutshellWindowModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellWindowModuleInterface* createWindowModule_t();
typedef void destroyWindowModule_t(NutshellWindowModuleInterface*);
#endif