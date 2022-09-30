#pragma once
#include "ntsh_module_interface.h"

class NutshellScriptingModuleInterface : public NutshellModuleInterface {
protected:
public:
    NutshellScriptingModuleInterface() {}
    NutshellScriptingModuleInterface(const std::string& name) : NutshellModuleInterface(NTSH_MODULE_SCRIPTING, name) {}
    virtual ~NutshellScriptingModuleInterface() {}

    virtual void init() = 0;
    virtual void update(double dt) = 0;
    virtual void destroy() = 0;
};

#ifdef NTSH_OS_WINDOWS
typedef NutshellScriptingModuleInterface* (__stdcall *createScriptingModule_t)();
typedef void (__stdcall *destroyScriptingModule_t)(NutshellScriptingModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellScriptingModuleInterface* createScriptingModule_t();
typedef void destroyScriptingModule_t(NutshellScriptingModuleInterface*);
#endif