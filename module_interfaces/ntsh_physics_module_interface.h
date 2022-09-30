#pragma once
#include "ntsh_module_interface.h"

class NutshellPhysicsModuleInterface : public NutshellModuleInterface {
protected:
public:
    NutshellPhysicsModuleInterface() {}
    NutshellPhysicsModuleInterface(const std::string& name) : NutshellModuleInterface(NTSH_MODULE_PHYSICS, name) {}
    virtual ~NutshellPhysicsModuleInterface() {}

    virtual void init() = 0;
    virtual void update(double dt) = 0;
    virtual void destroy() = 0;
};

#ifdef NTSH_OS_WINDOWS
typedef NutshellPhysicsModuleInterface* (__stdcall *createPhysicsModule_t)();
typedef void (__stdcall *destroyPhysicsModule_t)(NutshellPhysicsModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellPhysicsModuleInterface* createPhysicsModule_t();
typedef void destroyPhysicsModule_t(NutshellPhysicsModuleInterface*);
#endif