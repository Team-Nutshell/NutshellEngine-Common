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