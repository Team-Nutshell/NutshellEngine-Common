#pragma once
#include "../utils/ntshengn_utils_math.h"
#include <vector>
#include <memory>

#define NTSHENGN_SCRIPT(scriptName) \
	protected: \
		scriptName* cloneImpl() { return new scriptName(*this); }

namespace NtshEngn {

	// Collision info
	struct CollisionInfo {
		using Entity = uint32_t;

		Entity otherEntity = 0xFFFFFFFF;
		Math::vec3 normal;
		float depth = 0.0f;
		std::vector<Math::vec3> relativePoints;
	};

	// Script
	struct ScriptBase {
		virtual ~ScriptBase() = default;

		std::unique_ptr<ScriptBase> clone() { return std::unique_ptr<ScriptBase>(cloneImpl()); }

	public:
		virtual void onCollisionEnter(CollisionInfo collisionInfo) {
			NTSHENGN_UNUSED(collisionInfo);
		}
		virtual void onCollisionStill(CollisionInfo collisionInfo) {
			NTSHENGN_UNUSED(collisionInfo);
		}
		virtual void onCollisionExit(CollisionInfo collisionInfo) {
			NTSHENGN_UNUSED(collisionInfo);
		}

	protected:
		virtual ScriptBase* cloneImpl() = 0;
	};

}