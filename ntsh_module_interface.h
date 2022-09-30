#pragma once
#include "ecs.h"
#include <string>

class NutshellModuleInterface : public System {
protected:
    NtshModuleType m_type = NTSH_MODULE_UNKNOWN;
    std::string m_name = "";
public:
    NutshellModuleInterface() {}
    NutshellModuleInterface(const NtshModuleType type, const std::string& name) : m_type(type), m_name(name) {}
    virtual ~NutshellModuleInterface() {}

    virtual void init() = 0;
    virtual void update(double dt) = 0;
    virtual void destroy() = 0;

    const NtshModuleType getType() const {
        return m_type;
    }

    const std::string& getName() const {
        return m_name;
    }
};

#ifdef NTSH_OS_WINDOWS
typedef NutshellModuleInterface* (__stdcall *createModule_t)();
typedef void (__stdcall *destroyModule_t)(NutshellModuleInterface*);
#elif NTSH_OS_LINUX
typedef NutshellModuleInterface* createModule_t();
typedef void destroyModule_t(NutshellModuleInterface*);
#endif