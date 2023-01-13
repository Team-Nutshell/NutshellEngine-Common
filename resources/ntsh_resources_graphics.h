#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include <utility>

// Image
enum class NtshImageFormat {
	R8,
	R8G8,
	R8G8B8,
	R8G8B8A8,
	R16,
	R16G16,
	R16G16B16,
	R16G16B16A16,
	R32,
	R32G32,
	R32G32B32,
	R32G32B32A32,
	Unknown
};

enum class NtshImageColorSpace {
	Linear,
	SRGB,
	Unknown
};

struct NtshImage {
	// Image width
	uint32_t width = 0;
	
	// Image height
	uint32_t height = 0;

	// Image format
	NtshImageFormat format = NtshImageFormat::Unknown;

	// Image color space
	NtshImageColorSpace colorSpace = NtshImageColorSpace::Unknown;

	// Data
	std::vector<uint8_t> data;
};

// Material
struct NtshMaterial {
	// Diffuse (base color) texture
	NtshImage* diffuseTexture = nullptr;

	// Normal texture
	NtshImage* normalTexture = nullptr;

	// Metalness, Roughness and Occlusion textures can be the same one
	// In that case, R = Occlusion, G = Roughness, B = Metalness
	// Metalness texture
	NtshImage* metalnessTexture = nullptr;

	// Roughness texture
	NtshImage* roughnessTexture = nullptr;
	
	// Occlusion texture
	NtshImage* occlusionTexture = nullptr;
	
	// Emissive texture
	NtshImage* emissiveTexture = nullptr;
};

// Vertex
struct NtshVertex {
	std::array<float, 3> position = { 0.0f, 0.0f, 0.0f };
	std::array<float, 3> normal = { 0.0f, 0.0f, 0.0f };
	std::array<float, 2> uv = { 0.0f, 0.0f };
	std::array<float, 3> color = { 0.0f, 0.0f, 0.0f };
	std::array<float, 4> tangent = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::array<float, 4> joints = { 0.0f, 0.0f, 0.0f, 0.0f };
	std::array<float, 4> weights = { 0.0f, 0.0f, 0.0f, 0.0f };
};

// Mesh
enum class NtshMeshTopology {
	TriangleList,
	TriangleStrip,
	LineList,
	LineStrip,
	PointList,
	Unknown
};

struct NtshMesh {
	std::vector<NtshVertex> vertices;
	std::vector<uint32_t> indices;
	NtshMeshTopology topology = NtshMeshTopology::Unknown;
};

// Model
struct NtshModel {
	std::vector<std::pair<NtshMesh, NtshMaterial>> primitives;
};