#pragma once
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
	// Spot Light : position = Transform.position, direction = Transform.rotation, cutoffs = Transform.scale.xy
	struct Light {
		LightType type = LightType::Unknown;
		std::array<float, 3> color = { 0.0f, 0.0f, 0.0f };
	};

}