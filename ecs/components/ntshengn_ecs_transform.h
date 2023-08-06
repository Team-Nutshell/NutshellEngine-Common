#pragma once
#include "../../utils/ntshengn_utils_math.h"
#include <array>

namespace NtshEngn {

	struct Transform {
		Math::vec3 position = { 0.0f, 0.0f, 0.0f };
		Math::vec3 rotation = { 0.0f, 0.0f, 0.0f };
		Math::vec3 scale = { 1.0f, 1.0f, 1.0f };
	};

}