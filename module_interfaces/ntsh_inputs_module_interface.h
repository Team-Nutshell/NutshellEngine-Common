#pragma once
#include "ntsh_module_interface.h"

class NutshellInputsModuleInterface : public NutshellModuleInterface {
protected:
public:
    NutshellInputsModuleInterface() {}
    NutshellInputsModuleInterface(const std::string& name) : NutshellModuleInterface(NTSH_MODULE_INPUTS, name) {}
    virtual ~NutshellInputsModuleInterface() {}

    virtual void init() = 0;
    virtual void update(double dt) = 0;
    virtual void destroy() = 0;
};

#ifdef NTSH_OS_WINDOWS
typedef NutshellInputsModuleInterface* (__stdcall *createInputsModule_t)();
typedef void (__stdcall *destroyInputsModule_t)(NutshellInputsModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellInputsModuleInterface* createInputsModule_t();
typedef void destroyInputsModule_t(NutshellInputsModuleInterface*);
#endif