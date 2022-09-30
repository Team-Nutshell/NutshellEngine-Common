#pragma once
#include "ntsh_module_interface.h"

class NutshellNetworkModuleInterface : public NutshellModuleInterface {
protected:
public:
    NutshellNetworkModuleInterface() {}
    NutshellNetworkModuleInterface(const std::string& name) : NutshellModuleInterface(NTSH_MODULE_NETWORK, name) {}
    virtual ~NutshellNetworkModuleInterface() {}

    virtual void init() = 0;
    virtual void update(double dt) = 0;
    virtual void destroy() = 0;
};

#ifdef NTSH_OS_WINDOWS
typedef NutshellNetworkModuleInterface* (__stdcall *createNetworkModule_t)();
typedef void (__stdcall *destroyNetworkModule_t)(NutshellNetworkModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellNetworkModuleInterface* createNetworkModule_t();
typedef void destroyNetworkModule_t(NutshellNetworkModuleInterface*);
#endif