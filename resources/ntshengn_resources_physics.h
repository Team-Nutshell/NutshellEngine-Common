#pragma once
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
		ColliderShape(const ColliderShapeType shapeType): type(shapeType) {}

		ColliderShapeType type = ColliderShapeType::Unknown;
	};

	struct ColliderSphere: public ColliderShape {
		ColliderSphere(): ColliderShape(ColliderShapeType::Sphere) {}

		std::array<float, 3> center = { 0.0f, 0.0f, 0.0f };
		float radius = 0.0f;
	};

	struct ColliderAABB: public ColliderShape {
		ColliderAABB(): ColliderShape(ColliderShapeType::AABB) {}

		std::array<float, 3> min = { 0.0f, 0.0f, 0.0f };
		std::array<float, 3> max = { 0.0f, 0.0f, 0.0f };
	};

	struct ColliderCapsule: public ColliderShape {
		ColliderCapsule(): ColliderShape(ColliderShapeType::Capsule) {}

		std::array<float, 3> base = { 0.0f, 0.0f, 0.0f };
		std::array<float, 3> tip = { 0.0f, 0.0f, 0.0f };
		float radius = 0.0f;
	};

}