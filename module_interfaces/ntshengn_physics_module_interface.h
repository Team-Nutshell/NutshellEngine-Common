#pragma once
#include "ntshengn_module_interface.h"
#include "../resources/ntshengn_resources_physics.h"

namespace NtshEngn {

	class PhysicsModuleInterface : public ModuleInterface {
	public:
		PhysicsModuleInterface() {}
		PhysicsModuleInterface(const std::string& name) : ModuleInterface(ModuleType::Physics, name) {}
		virtual ~PhysicsModuleInterface() {}

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		// Returns an IntersectionInformation structure containing information about the intersection
		virtual IntersectionInformation intersect(const ColliderShape* shape1, const ColliderShape* shape2) = 0;
	};

}