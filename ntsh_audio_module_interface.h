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