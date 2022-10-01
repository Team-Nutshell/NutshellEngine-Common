#pragma once
#include "ntsh_module_interface.h"

class NutshellGraphicsModuleInterface : public NutshellModuleInterface {
protected:
public:
	NutshellGraphicsModuleInterface() {}
	NutshellGraphicsModuleInterface(const std::string& name) : NutshellModuleInterface(NTSH_MODULE_GRAPHICS, name) {}
	virtual ~NutshellGraphicsModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;
};

#ifdef NTSH_OS_WINDOWS
typedef NutshellGraphicsModuleInterface* (__stdcall *createGraphicsModule_t)();
typedef void (__stdcall *destroyGraphicsModule_t)(NutshellGraphicsModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellGraphicsModuleInterface* createGraphicsModule_t();
typedef void destroyGraphicsModule_t(NutshellGraphicsModuleInterface*);
#endif