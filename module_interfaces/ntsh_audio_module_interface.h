#pragma once
#include "ntsh_module_interface.h"

class NutshellAudioModuleInterface : public NutshellModuleInterface {
protected:
public:
    NutshellAudioModuleInterface() {}
    NutshellAudioModuleInterface(const std::string& name) : NutshellModuleInterface(NTSH_MODULE_AUDIO, name) {}
    virtual ~NutshellAudioModuleInterface() {}

    virtual void init() = 0;
    virtual void update(double dt) = 0;
    virtual void destroy() = 0;
};

#ifdef NTSH_OS_WINDOWS
typedef NutshellAudioModuleInterface* (__stdcall *createAudioModule_t)();
typedef void (__stdcall *destroyAudioModule_t)(NutshellAudioModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellAudioModuleInterface* createAudioModule_t();
typedef void destroyAudioModule_t(NutshellAudioModuleInterface*);
#endif