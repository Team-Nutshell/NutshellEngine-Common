#pragma once
#include "../utils/ntshengn_utils_math.h"
#include <array>

namespace NtshEngn {

	// Collision
	enum class ColliderShapeType {
		Sphere,
		AABB,
		Capsule,
		Unknown
	};

	struct ColliderShape {
		ColliderShape(const ColliderShapeType shapeType) : type(shapeType) {}

		ColliderShapeType getType() const { return type; }

	private:
		ColliderShapeType type = ColliderShapeType::Unknown;
	};

	struct ColliderSphere: public ColliderShape {
		ColliderSphere() : ColliderShape(ColliderShapeType::Sphere) {}

		Math::vec3 center = { 0.0f, 0.0f, 0.0f };
		float radius = 0.0f;
	};

	struct ColliderAABB: public ColliderShape {
		ColliderAABB() : ColliderShape(ColliderShapeType::AABB) {}

		Math::vec3 min = { 0.0f, 0.0f, 0.0f };
		Math::vec3 max = { 0.0f, 0.0f, 0.0f };
	};

	struct ColliderCapsule: public ColliderShape {
		ColliderCapsule() : ColliderShape(ColliderShapeType::Capsule) {}

		Math::vec3 base = { 0.0f, 0.0f, 0.0f };
		Math::vec3 tip = { 0.0f, 0.0f, 0.0f };
		float radius = 0.0f;
	};

	struct IntersectionInformation {
		bool hasIntersected = false;
		Math::vec3 intersectionNormal = { 0.0f, 0.0f, 0.0f };
		float intersectionDepth = 0.0f;
	};

	// Raycast
	struct RaycastInformation {
		using Entity = uint32_t;

		Entity entity;
		float distance = 0.0f;
	};

}