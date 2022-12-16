#pragma once
#include "ntsh_module_interface.h"

class NutshellPhysicsModuleInterface : public NutshellModuleInterface {
public:
	NutshellPhysicsModuleInterface() {}
	NutshellPhysicsModuleInterface(const std::string& name) : NutshellModuleInterface(NtshModuleType::Physics, name) {}
	virtual ~NutshellPhysicsModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;
};