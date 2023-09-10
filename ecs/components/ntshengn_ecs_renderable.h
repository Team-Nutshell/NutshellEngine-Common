#pragma once
#include "../../resources/ntshengn_resources_graphics.h"

namespace NtshEngn {

	struct Renderable {
		Model* model = nullptr;
		uint32_t modelPrimitiveIndex = 0;
	};

}