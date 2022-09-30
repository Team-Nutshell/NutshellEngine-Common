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