#pragma once
#include "../../utils/ntshengn_utils_math.h"
#include <array>

namespace NtshEngn {

	enum class LightType {
		Directional,
		Point,
		Spot,
		Unknown
	};

	// Directional Light : direction = Transform.rotation
	// Point Light : position = Transform.position
	// Spot Light : position = Transform.position, direction = Transform.rotation
	struct Light {
		LightType type = LightType::Unknown;
		Math::vec3 color = { 0.0f, 0.0f, 0.0f };
		Math::vec2 cutoff = { 0.0f, 0.0f };
	};

}