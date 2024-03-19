#pragma once
#include "ntshengn_system_module_interface.h"
#include "../resources/ntshengn_resources_physics.h"
#include <vector>
#include <utility>

namespace NtshEngn {

	class PhysicsModuleInterface : public SystemModuleInterface {
	public:
		PhysicsModuleInterface() {}
		PhysicsModuleInterface(const std::string& name) : SystemModuleInterface(ModuleType::Physics, name) {}
		virtual ~PhysicsModuleInterface() {}

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		// Returns an IntersectionInformation structure containing information about the intersection
		virtual IntersectionInformation intersect(const ColliderShape* shape1, const ColliderShape* shape2) = 0;
		
		// Returns a RaycastInformation structure containinng informationn about the raycast
		virtual RaycastInformation raycast(const Math::vec3& rayOrigin, const Math::vec3& rayDirection, float tMin, float tMax, const ColliderShape* shape) = 0;
		// Returns a list of RaycastInformation structures containing information about the hit entities
		virtual std::vector<std::pair<Entity, RaycastInformation>> raycastAll(const Math::vec3& rayOrigin, const Math::vec3& rayDirection, float tMin, float tMax) = 0;
	};

}