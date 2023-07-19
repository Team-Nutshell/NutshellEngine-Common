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

#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_ASSET_MANAGER_INFO(message) \
	do { \
		std::cerr << "\33[1m\33[94mASSET MANAGER \33[34mINFO\33[39m\33[0m: " << message << std::endl; \
	} while(0)
#else
#define NTSHENGN_ASSET_MANAGER_INFO(message) \
	do { \
	} while(0)
#endif

#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_ASSET_MANAGER_WARNING(message) \
	do { \
		std::cerr << "\33[1m\33[94mASSET MANAGER \33[93mWARNING\33[39m\33[0m: " << message << std::endl; \
	} while(0)
#else
#define NTSHENGN_ASSET_MANAGER_WARNING(message) \
	do { \
	} while(0)
#endif

#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_ASSET_MANAGER_ERROR(message, code) \
	do { \
		std::cerr << "\33[1m\33[94mASSET MANAGER \33[31mERROR\33[39m\33[0m: " << message << " (" << #code << ")" << std::endl; \
		exit(1); \
	} while(0)
#else
#define NTSHENGN_ASSET_MANAGER_ERROR(message, code) \
	do { \
		exit(1); \
	} while(0)
#endif

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

		void calculateTangents(Mesh& mesh) {
			if (m_assetLoaderModule) {
				m_assetLoaderModule->calculateTangents(mesh);
			}
			else {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not calculate tangent for mesh.");
			}
		}

		std::array<std::array<float, 3>, 2> calculateAABB(const Mesh& mesh) {
			if (m_assetLoaderModule) {
				return m_assetLoaderModule->calculateAABB(mesh);
			}
			else {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not calculate AABB for mesh.");

				return { std::array<float, 3>{ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
			}
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