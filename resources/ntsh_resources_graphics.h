#pragma once
#include <cstdint>
#include <vector>
#include <utility>

// Image
typedef enum NtshImageFormat {
	NTSH_IMAGE_FORMAT_R8,
	NTSH_IMAGE_FORMAT_R8G8,
	NTSH_IMAGE_FORMAT_R8G8B8,
	NTSH_IMAGE_FORMAT_R8G8B8A8,
	NTSH_IMAGE_FORMAT_R16,
	NTSH_IMAGE_FORMAT_R16G16,
	NTSH_IMAGE_FORMAT_R16G16B16,
	NTSH_IMAGE_FORMAT_R16G16B16A16,
	NTSH_IMAGE_FORMAT_R32,
	NTSH_IMAGE_FORMAT_R32G32,
	NTSH_IMAGE_FORMAT_R32G32B32,
	NTSH_IMAGE_FORMAT_R32G32B32A32,
	NTSH_IMAGE_FORMAT_UNKNOWN
} NtshImageFormat;

struct NtshImage {
	// Image width
	uint32_t width = 0;
	
	// Image height
	uint32_t height = 0;

	// Image format
	NtshImageFormat format = NTSH_IMAGE_FORMAT_UNKNOWN;

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
	float position[3] = { 0.0f, 0.0f, 0.0f };
	float normal[3] = { 0.0f, 0.0f, 0.0f };
	float uv[2] = { 0.0f, 0.0f };
	float color[3] = { 0.0f, 0.0f, 0.0f };
	float tangent[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float joints[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float weights[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
};

// Mesh
typedef enum NtshTopology {
	NTSH_TOPOLOGY_TRIANGLE_LIST,
	NTSH_TOPOLOGY_TRIANGLE_STRIP,
	NTSH_TOPOLOGY_LINE_LIST,
	NTSH_TOPOLOGY_LINE_STRIP,
	NTSH_TOPOLOGY_POINT_LIST
} NtshTopology;

struct NtshMesh {
	std::vector<NtshVertex> vertices;
	std::vector<uint32_t> indices;
	NtshTopology topology = NTSH_TOPOLOGY_TRIANGLE_LIST;
};

// Model
struct NtshModel {
	std::vector<std::pair<NtshMesh, NtshMaterial>> primitives;
};