#pragma once
#include "../module_interfaces/ntshengn_asset_loader_module_interface.h"
#include "../resources/ntshengn_resources_audio.h"
#include "../resources/ntshengn_resources_graphics.h"
#include "../utils/ntshengn_defines.h"
#include <string>
#include <forward_list>
#include <iterator>
#include <cmath>
#include <array>
#include <utility>
#include <filesystem>

namespace NtshEngn {

	class AssetManager {
	public:
		Sound* createSound() {
			Sound newSound;
			m_soundResources.push_front(newSound);

			return &m_soundResources.front();
		}

		Sound* loadSound(const std::string& filePath) {
			if (!std::filesystem::exists(filePath)) {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not load sound file \"" + filePath + "\" (file does not exist).");

				return nullptr;
			}
			
			Sound newSound;
			if (m_assetLoaderModule) {
				newSound = m_assetLoaderModule->loadSound(filePath);
			}

			if (newSound.size != 0) {
				m_soundResources.push_front(newSound);

				return &m_soundResources.front();
			}
			else {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not load sound file \"" + filePath + "\".");

				return nullptr;
			}
		}

		Model* createModel() {
			Model newModel;

			m_modelResources.push_front(newModel);

			return &m_modelResources.front();
		}

		Model* loadModel(const std::string& filePath) {
			if (!std::filesystem::exists(filePath)) {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not load model file \"" + filePath + "\" (file does not exist).");

				return nullptr;
			}

			Model newModel;
			if (m_assetLoaderModule) {
				newModel = m_assetLoaderModule->loadModel(filePath);
			}

			if (newModel.primitives.size() != 0) {
				m_modelResources.push_front(newModel);

				return &m_modelResources.front();
			}
			else {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not load model file \"" + filePath + "\".");

				return nullptr;
			}
		}

		Image* createImage() {
			Image newImage;

			m_imageResources.push_front(newImage);

			return &m_imageResources.front();
		}

		Image* loadImage(const std::string& filePath) {
			if (!std::filesystem::exists(filePath)) {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not load image file \"" + filePath + "\" (file does not exist).");

				return nullptr;
			}

			Image newImage;
			if (m_assetLoaderModule) {
				newImage = m_assetLoaderModule->loadImage(filePath);
			}

			if (newImage.width != 0) {
				m_imageResources.push_front(newImage);

				return &m_imageResources.front();
			}
			else {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not load image file \"" + filePath + "\".");

				return nullptr;
			}
		}

		void destroySound(Sound* sound) {
			std::forward_list<Sound>::iterator prev = m_soundResources.before_begin();
			for (std::forward_list<Sound>::iterator it = m_soundResources.begin(); it != m_soundResources.end(); it++) {
				if (sound == &(*it)) {
					m_soundResources.erase_after(prev);
					break;
				}

				prev = it;
			}

			NTSHENGN_ASSET_MANAGER_ERROR("Could not destroy sound resource.", Result::AssetManagerError);
		}

		void destroyModel(Model* model) {
			std::forward_list<Model>::iterator prev = m_modelResources.before_begin();
			for (std::forward_list<Model>::iterator it = m_modelResources.begin(); it != m_modelResources.end(); it++) {
				if (model == &(*it)) {
					m_modelResources.erase_after(prev);
					return;
				}

				prev = it;
			}

			NTSHENGN_ASSET_MANAGER_ERROR("Could not destroy model resource.", Result::AssetManagerError);
		}

		void destroyImage(Image* image) {
			std::forward_list<Image>::iterator prev = m_imageResources.before_begin();
			for (std::forward_list<Image>::iterator it = m_imageResources.begin(); it != m_imageResources.end(); it++) {
				if (image == &(*it)) {
					m_imageResources.erase_after(prev);
					return;
				}

				prev = it;
			}

			NTSHENGN_ASSET_MANAGER_ERROR("Could not destroy image resource.", Result::AssetManagerError);
		}

	public:
		static void calculateTangents(Mesh& mesh) {
			std::vector<std::array<float, 3>> tan1(mesh.vertices.size(), { 0.0f, 0.0f, 0.0f });
			std::vector<std::array<float, 3>> tan2(mesh.vertices.size(), { 0.0f, 0.0f, 0.0f });
			for (size_t i = 0; i < mesh.indices.size(); i += 3) {
				Vertex& vertex0 = mesh.vertices[mesh.indices[i]];
				Vertex& vertex1 = mesh.vertices[mesh.indices[i + 1]];
				Vertex& vertex2 = mesh.vertices[mesh.indices[i + 2]];

				const std::array<float, 3> dPos1 = { vertex1.position[0] - vertex0.position[0], vertex1.position[1] - vertex0.position[1], vertex1.position[2] - vertex0.position[2] };
				const std::array<float, 3> dPos2 = { vertex2.position[0] - vertex0.position[0], vertex2.position[1] - vertex0.position[1], vertex2.position[2] - vertex0.position[2] };

				const std::array<float, 2> dUV1 = { vertex1.uv[0] - vertex0.uv[0], vertex1.uv[1] - vertex0.uv[1] };
				const std::array<float, 2> dUV2 = { vertex2.uv[0] - vertex0.uv[0], vertex2.uv[1] - vertex0.uv[1] };

				const float r = 1.0f / (dUV1[0] * dUV2[1] - dUV1[1] * dUV2[0]);

				const std::array<float, 3> uDir = { (dPos1[0] * dUV2[1] - dPos2[0] * dUV1[1]) * r, (dPos1[1] * dUV2[1] - dPos2[1] * dUV1[1]) * r, (dPos1[2] * dUV2[1] - dPos2[2] * dUV1[1]) * r };
				const std::array<float, 3> vDir = { (dPos2[0] * dUV1[0] - dPos1[0] * dUV2[0]) * r, (dPos2[1] * dUV1[0] - dPos1[1] * dUV2[0]) * r, (dPos2[2] * dUV1[0] - dPos1[2] * dUV2[0]) * r };

				tan1[mesh.indices[i]] = { tan1[mesh.indices[i]][0] + uDir[0], tan1[mesh.indices[i]][1] + uDir[1], tan1[mesh.indices[i]][2] + uDir[2] };
				tan1[mesh.indices[i + 1]] = { tan1[mesh.indices[i + 1]][0] + uDir[0], tan1[mesh.indices[i + 1]][1] + uDir[1], tan1[mesh.indices[i + 1]][2] + uDir[2] };
				tan1[mesh.indices[i + 2]] = { tan1[mesh.indices[i + 2]][0] + uDir[0], tan1[mesh.indices[i + 2]][1] + uDir[1], tan1[mesh.indices[i + 2]][2] + uDir[2] };

				tan2[mesh.indices[i]] = { tan2[mesh.indices[i]][0] + vDir[0], tan2[mesh.indices[i]][1] + vDir[1], tan2[mesh.indices[i]][2] + vDir[2] };
				tan2[mesh.indices[i + 1]] = { tan2[mesh.indices[i + 1]][0] + vDir[0], tan2[mesh.indices[i + 1]][1] + vDir[1], tan2[mesh.indices[i + 1]][2] + vDir[2] };
				tan2[mesh.indices[i + 2]] = { tan2[mesh.indices[i + 2]][0] + vDir[0], tan2[mesh.indices[i + 2]][1] + vDir[1], tan2[mesh.indices[i + 2]][2] + vDir[2] };
			}

			for (size_t i = 0; i < mesh.vertices.size(); i++) {
				const float ndott = mesh.vertices[i].normal[0] * tan1[i][0] + mesh.vertices[i].normal[1] * tan1[i][1] + mesh.vertices[i].normal[2] * tan1[i][2];
				const std::array<float, 3> ncrosst = { mesh.vertices[i].normal[1] * tan1[i][2] - mesh.vertices[i].normal[2] * tan1[i][1], mesh.vertices[i].normal[2] * tan1[i][0] - mesh.vertices[i].normal[0] * tan1[i][2], mesh.vertices[i].normal[0] * tan1[i][1] - mesh.vertices[i].normal[1] * tan1[i][0] };

				const std::array<float, 3> unnormalizedTangent = { tan1[i][0] - mesh.vertices[i].normal[0] * ndott, tan1[i][1] - mesh.vertices[i].normal[1] * ndott, tan1[i][2] - mesh.vertices[i].normal[2] * ndott };
				const float unnormalizedTangentLength = std::sqrt(unnormalizedTangent[0] * unnormalizedTangent[0] + unnormalizedTangent[1] * unnormalizedTangent[1] + unnormalizedTangent[2] * unnormalizedTangent[2]);
				const std::array<float, 3> normalizedTangent = { unnormalizedTangent[0] / unnormalizedTangentLength, unnormalizedTangent[1] / unnormalizedTangentLength, unnormalizedTangent[2] / unnormalizedTangentLength };
				const float tangentSign = (ncrosst[0] * tan2[i][0] + ncrosst[1] * tan2[i][1] + ncrosst[2] * tan2[i][2]) < 0.0f ? -1.0f : 1.0f;

				mesh.vertices[i].tangent = { normalizedTangent[0], normalizedTangent[1], normalizedTangent[2], tangentSign };
			}
		}

		static std::pair<std::array<float, 3>, std::array<float, 3>> calculateAABB(const Mesh& mesh) {
			std::array<float, 3> min = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
			std::array<float, 3> max = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
			for (const Vertex& vertex : mesh.vertices) {
				if (vertex.position[0] < min[0]) {
					min[0] = vertex.position[0];
				}
				if (vertex.position[0] > max[0]) {
					max[0] = vertex.position[0];
				}

				if (vertex.position[1] < min[1]) {
					min[1] = vertex.position[1];
				}
				if (vertex.position[1] > max[1]) {
					max[1] = vertex.position[1];
				}

				if (vertex.position[2] < min[2]) {
					min[2] = vertex.position[2];
				}
				if (vertex.position[2] > max[2]) {
					max[2] = vertex.position[2];
				}
			}

			const float epsilon = 0.0001f;

			if (min[0] == max[0]) {
				min[0] -= epsilon;
				max[0] += epsilon;
			}

			if (min[1] == max[1]) {
				min[1] -= epsilon;
				max[1] += epsilon;
			}

			if (min[2] == max[2]) {
				min[2] -= epsilon;
				max[2] += epsilon;
			}

			return { min, max };
		}

	public:
		void setAssetLoaderModule(AssetLoaderModuleInterface* assetLoaderModule) {
			m_assetLoaderModule = assetLoaderModule;
		}

	private:
		AssetLoaderModuleInterface* m_assetLoaderModule;

		std::forward_list<Sound> m_soundResources;
		std::forward_list<Model> m_modelResources;
		std::forward_list<Image> m_imageResources;
	};

}