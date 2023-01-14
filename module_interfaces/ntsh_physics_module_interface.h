#pragma once
#include "ntsh_module_interface.h"
#include "../resources/ntsh_resources_physics.h"

class NutshellPhysicsModuleInterface : public NutshellModuleInterface {
public:
	NutshellPhysicsModuleInterface() {}
	NutshellPhysicsModuleInterface(const std::string& name) : NutshellModuleInterface(Ntsh::ModuleType::Physics, name) {}
	virtual ~NutshellPhysicsModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;

	// Returns true if the two shapes are intersecting with each other, else, returns false
	virtual bool intersect(Ntsh::ColliderShape* shape1, Ntsh::ColliderShape* shape2) = 0;
};