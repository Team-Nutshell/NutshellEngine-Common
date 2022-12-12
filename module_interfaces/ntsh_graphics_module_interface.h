#pragma once
#include "ntsh_module_interface.h"

class NutshellGraphicsModuleInterface : public NutshellModuleInterface {
protected:
public:
	NutshellGraphicsModuleInterface() {}
	NutshellGraphicsModuleInterface(const std::string& name) : NutshellModuleInterface(NtshModuleType::Graphics, name) {}
	virtual ~NutshellGraphicsModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;
};