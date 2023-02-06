#pragma once

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
		LightType type;
		float color[3];
	};

}