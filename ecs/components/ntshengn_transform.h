#pragma once
#include <array>

namespace NtshEngn {

	struct Transform {
		std::array<float, 3> position = { 0.0f, 0.0f, 0.0f };
		std::array<float, 3> rotation = { 0.0f, 0.0f, 0.0f };
		std::array<float, 3> scale = { 1.0f, 1.0f, 1.0f };
	};

}