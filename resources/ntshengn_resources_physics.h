#pragma once
#include "../utils/ntshengn_utils_math.h"

namespace NtshEngn {

	// Collision
	enum class ColliderShapeType {
		Sphere,
		AABB,
		OBB,
		Capsule,
		Unknown
	};

	struct ColliderShape {
		ColliderShape(const ColliderShapeType shapeType) : type(shapeType) {}
		virtual ~ColliderShape() = default;

		ColliderShapeType getType() const { return type; }

		std::unique_ptr<ColliderShape> clone() { return std::unique_ptr<ColliderShape>(cloneImpl()); }

	protected:
		virtual ColliderShape* cloneImpl() = 0;
		
	private:
		ColliderShapeType type = ColliderShapeType::Unknown;
	};

	struct ColliderSphere : public ColliderShape {
		ColliderSphere() : ColliderShape(ColliderShapeType::Sphere) {}

		ColliderSphere* cloneImpl() { return new ColliderSphere(*this); }

		Math::vec3 center = { 0.0f, 0.0f, 0.0f };
		float radius = 0.0f;
	};

	struct ColliderAABB : public ColliderShape {
		ColliderAABB() : ColliderShape(ColliderShapeType::AABB) {}

		ColliderAABB* cloneImpl() { return new ColliderAABB(*this); }

		Math::vec3 min = { 0.0f, 0.0f, 0.0f };
		Math::vec3 max = { 0.0f, 0.0f, 0.0f };
	};

	struct ColliderOBB : public ColliderShape {
		ColliderOBB() : ColliderShape(ColliderShapeType::OBB) {}

		ColliderOBB* cloneImpl() { return new ColliderOBB(*this); }

		Math::vec3 center = { 0.0f, 0.0f, 0.0f };
		Math::vec3 halfExtent = { 0.0f, 0.0f, 0.0f };
		Math::vec3 rotation = { 0.0f, 0.0f, 0.0f }; 
	};

	struct ColliderCapsule : public ColliderShape {
		ColliderCapsule() : ColliderShape(ColliderShapeType::Capsule) {}

		ColliderCapsule* cloneImpl() { return new ColliderCapsule(*this); }

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
		Math::vec3 normal = { 0.0f, 0.0f, 0.0f };
	};

}