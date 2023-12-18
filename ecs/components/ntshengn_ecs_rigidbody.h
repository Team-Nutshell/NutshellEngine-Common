#pragma once
#include "../../utils/ntshengn_utils_math.h"
#include <array>

namespace NtshEngn {

	struct Rigidbody {
		bool isStatic = false;
		bool isAffectedByConstants = true;
		float mass = 1.0f;
		float inertia = 1.0f;
		float restitution = 0.0f;
		float staticFriction = 0.0f;
		float dynamicFriction = 0.0f;
		
		Math::vec3 force = Math::vec3(0.0f, 0.0f, 0.0f);
		Math::vec3 torque = Math::vec3(0.0f, 0.0f, 0.0f);
	};

}