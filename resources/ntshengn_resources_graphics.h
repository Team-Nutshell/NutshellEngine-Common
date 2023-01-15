#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include <utility>

namespace NtshEngn {

	// Image
	typedef uint64_t ImageId;

	enum class ImageFormat {
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

	enum class ImageColorSpace {
		Linear,
		SRGB,
		Unknown
	};

	struct Image {
		// Image width
		uint32_t width = 0;
		
		// Image height
		uint32_t height = 0;

		// Image format
		ImageFormat format = ImageFormat::Unknown;

		// Image color space
		ImageColorSpace colorSpace = ImageColorSpace::Unknown;

		// Data
		std::vector<uint8_t> data;
	};

	// Material
	struct Material {
		// Diffuse (base color) texture
		Image* diffuseTexture = nullptr;

		// Normal texture
		Image* normalTexture = nullptr;

		// Metalness, Roughness and Occlusion textures can be the same one
		// In that case, R = Occlusion, G = Roughness, B = Metalness
		// Metalness texture
		Image* metalnessTexture = nullptr;

		// Roughness texture
		Image* roughnessTexture = nullptr;
		
		// Occlusion texture
		Image* occlusionTexture = nullptr;
		
		// Emissive texture
		Image* emissiveTexture = nullptr;
	};

	// Mesh
	typedef uint64_t MeshId;

	enum class MeshTopology {
		TriangleList,
		TriangleStrip,
		LineList,
		LineStrip,
		PointList,
		Unknown
	};

	// Vertex
	struct Vertex {
		std::array<float, 3> position = { 0.0f, 0.0f, 0.0f };
		std::array<float, 3> normal = { 0.0f, 0.0f, 0.0f };
		std::array<float, 2> uv = { 0.0f, 0.0f };
		std::array<float, 3> color = { 0.0f, 0.0f, 0.0f };
		std::array<float, 4> tangent = { 0.0f, 0.0f, 0.0f, 0.0f };
		std::array<float, 4> joints = { 0.0f, 0.0f, 0.0f, 0.0f };
		std::array<float, 4> weights = { 0.0f, 0.0f, 0.0f, 0.0f };
	};

	struct Mesh {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		MeshTopology topology = MeshTopology::Unknown;
	};

	// Model
	struct Model {
		std::vector<std::pair<Mesh, Material>> primitives;
	};

}