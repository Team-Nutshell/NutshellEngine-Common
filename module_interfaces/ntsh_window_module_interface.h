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
};

#ifdef NTSH_OS_WINDOWS
typedef NutshellWindowModuleInterface* (__stdcall *createWindowModule_t)();
typedef void (__stdcall *destroyWindowModule_t)(NutshellWindowModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellWindowModuleInterface* createWindowModule_t();
typedef void destroyWindowModule_t(NutshellWindowModuleInterface*);
#endif