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

#ifdef NTSH_OS_WINDOWS
typedef NutshellAnimationModuleInterface* (__stdcall *createAnimationModule_t)();
typedef void (__stdcall *destroyAnimationModule_t)(NutshellAnimationModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellAnimationModuleInterface* createAnimationModule_t();
typedef void destroyAnimationModule_t(NutshellAnimationModuleInterface*);
#endif