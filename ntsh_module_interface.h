#pragma once
#include "ecs.h"
#include <string>

class NutshellModuleInterface : public System {
protected:
    std::string m_name = "";
public:
    NutshellModuleInterface() {}
    virtual ~NutshellModuleInterface() {}

    virtual void init() = 0;
    virtual void update(double dt) = 0;
    virtual void destroy() = 0;

    const std::string& getName() const {
        return m_name;
    }
};

typedef NutshellModuleInterface* createModule_t();
typedef void destroyModule_t(NutshellModuleInterface*);