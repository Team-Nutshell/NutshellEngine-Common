#pragma once
#include "ntsh_module_interface.h"

class NutshellAnimationModuleInterface : public NutshellModuleInterface {
protected:
public:
    NutshellAnimationModuleInterface() {}
    NutshellAnimationModuleInterface(const std::string& name) : NutshellModuleInterface(NTSH_MODULE_ANIMATION, name) {}
    virtual ~NutshellAnimationModuleInterface() {}

    virtual void init() = 0;
    virtual void update(double dt) = 0;
    virtual void destroy() = 0;
};