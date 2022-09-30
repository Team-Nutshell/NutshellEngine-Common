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