#pragma once
#include <array>

namespace NtshEngn {

	struct Rigidbody {
		std::array<float, 3> force = { 0.0f, 0.0f, 0.0f };
		float mass = 1.0f;
	};

}