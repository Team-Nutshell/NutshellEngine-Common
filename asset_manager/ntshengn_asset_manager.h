#pragma once
#include "../module_interfaces/ntshengn_asset_loader_module_interface.h"
#include "../resources/ntshengn_resources_audio.h"
#include "../resources/ntshengn_resources_graphics.h"
#include "../utils/ntshengn_defines.h"
#include "../utils/ntshengn_utils_bimap.h"
#include "../utils/ntshengn_utils_file.h"
#include "../utils/ntshengn_utils_json.h"
#include "../utils/ntshengn_utils_math.h"
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

			if (m_soundPaths.exist(filePath)) {
				return m_soundPaths[filePath];
			}
			
			Sound newSound;
			if (File::extension(filePath) == "ntsd") {
				loadSoundNtsd(filePath, newSound);
			}
			else {
				if (m_assetLoaderModule) {
					newSound = m_assetLoaderModule->loadSound(filePath);
				}
			}

			if (newSound.size != 0) {
				m_soundResources.push_front(newSound);

				m_soundPaths.insert_or_assign(filePath, &m_soundResources.front());

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

			if (m_modelPaths.exist(filePath)) {
				return m_modelPaths[filePath];
			}

			Model newModel;
			if (File::extension(filePath) == "ntmd") {
				loadModelNtmd(filePath, newModel);
			}
			else {
				if (m_assetLoaderModule) {
					newModel = m_assetLoaderModule->loadModel(filePath);
				}
			}

			if (newModel.primitives.size() != 0) {
				m_modelResources.push_front(newModel);

				m_modelPaths.insert_or_assign(filePath, &m_modelResources.front());

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

			if (m_imagePaths.exist(filePath)) {
				return m_imagePaths[filePath];
			}

			Image newImage;
			if (File::extension(filePath) == "ntim") {
				loadImageNtim(filePath, newImage);
			}
			else {
				if (m_assetLoaderModule) {
					newImage = m_assetLoaderModule->loadImage(filePath);
				}
			}

			if (newImage.width != 0) {
				m_imageResources.push_front(newImage);

				m_imagePaths.insert_or_assign(filePath, &m_imageResources.front());

				return &m_imageResources.front();
			}
			else {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not load image file \"" + filePath + "\".");

				return nullptr;
			}
		}

		Font* createFont() {
			Font newFont;

			m_fontResources.push_front(newFont);

			return &m_fontResources.front();
		}

		Font* loadFont(const std::string& filePath, float fontHeight) {
			if (!std::filesystem::exists(filePath)) {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not load font file \"" + filePath + "\" (file does not exist).");

				return nullptr;
			}

			if (fontHeight <= 0.0f) {
				NTSHENGN_ASSET_MANAGER_WARNING("Font height for font file \"" + filePath + "\" should be greater than 0.");

				return nullptr;
			}

			if (m_fontPaths.exist(filePath + "/" + std::to_string(fontHeight))) {
				return m_fontPaths[filePath + "/" + std::to_string(fontHeight)];
			}

			Font newFont;
			if (m_assetLoaderModule) {
				newFont = m_assetLoaderModule->loadFont(filePath, fontHeight);
			}

			if (newFont.image) {
				m_fontResources.push_front(newFont);

				m_fontPaths.insert_or_assign(filePath + "/" + std::to_string(fontHeight), &m_fontResources.front());

				return &m_fontResources.front();
			}
			else {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not load font file \"" + filePath + "\".");

				return nullptr;
			}
		}

		void destroySound(Sound* sound) {
			if (m_soundPaths.exist(sound)) {
				m_soundPaths.erase(sound);
			}

			std::forward_list<Sound>::iterator prev = m_soundResources.before_begin();
			for (std::forward_list<Sound>::iterator it = m_soundResources.begin(); it != m_soundResources.end(); it++) {
				if (sound == &(*it)) {
					m_soundResources.erase_after(prev);
					return;
				}

				prev = it;
			}
			
			NTSHENGN_ASSET_MANAGER_ERROR("Could not destroy sound resource.", Result::AssetManagerError);
		}

		void destroyModel(Model* model) {
			if (m_modelPaths.exist(model)) {
				m_modelPaths.erase(model);
			}

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
			if (m_imagePaths.exist(image)) {
				m_imagePaths.erase(image);
			}

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

		void destroyFont(Font* font) {
			if (m_fontPaths.exist(font)) {
				m_fontPaths.erase(font);
			}

			std::forward_list<Font>::iterator prev = m_fontResources.before_begin();
			for (std::forward_list<Font>::iterator it = m_fontResources.begin(); it != m_fontResources.end(); it++) {
				if (font == &(*it)) {
					m_fontResources.erase_after(prev);
					return;
				}

				prev = it;
			}

			NTSHENGN_ASSET_MANAGER_ERROR("Could not destroy font resource.", Result::AssetManagerError);
		}

		void calculateTangents(Mesh& mesh) {
			if (m_assetLoaderModule) {
				m_assetLoaderModule->calculateTangents(mesh);
			}
			else {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not calculate tangent for mesh.");
			}
		}

		std::array<Math::vec3, 2> calculateAABB(const Mesh& mesh) {
			if (m_assetLoaderModule) {
				return m_assetLoaderModule->calculateAABB(mesh);
			}
			else {
				NTSHENGN_ASSET_MANAGER_WARNING("Could not calculate AABB for mesh.");

				return { Math::vec3(0.0f, 0.0f, 0.0f), Math::vec3(0.0f, 0.0f, 0.0f) };
			}
		}

	public:
		void setAssetLoaderModule(AssetLoaderModuleInterface* assetLoaderModule) {
			m_assetLoaderModule = assetLoaderModule;
		}

	private:
		void loadSoundNtsd(const std::string& filePath, Sound& sound) {
			JSON json;
			const JSON::Node& soundRoot = json.read(filePath);

			if (soundRoot.contains("channels")) {
				sound.channels = static_cast<uint8_t>(soundRoot["channels"].getNumber());
			}

			if (soundRoot.contains("sampleRate")) {
				sound.sampleRate = static_cast<int32_t>(soundRoot["sampleRate"].getNumber());
			}

			if (soundRoot.contains("bitsPerSample")) {
				sound.bitsPerSample = static_cast<uint8_t>(soundRoot["bitsPerSample"].getNumber());
			}

			if (soundRoot.contains("size")) {
				sound.size = static_cast<size_t>(soundRoot["size"].getNumber());
			}

			if (soundRoot.contains("data")) {
				for (size_t i = 0; i < soundRoot["data"].size(); i++) {
					sound.data.push_back(static_cast<uint8_t>(soundRoot["data"][i].getNumber()));
				}
			}
		}

		void loadMeshNtmh(const std::string& filePath, Mesh& mesh) {
			const std::unordered_map<std::string, MeshTopology> stringToMeshTopology {
				{ "TriangleList", MeshTopology::TriangleList },
				{ "TriangleStrip", MeshTopology::TriangleStrip },
				{ "LineList", MeshTopology::LineList },
				{ "LineStrip", MeshTopology::LineStrip },
				{ "PointList", MeshTopology::PointList },
				{ "Unknown", MeshTopology::Unknown }
			};

			JSON json;
			const JSON::Node& meshRoot = json.read(filePath);

			bool hasNormals = false;
			bool hasUvs = false;
			bool hasIndices = false;
			bool hasTangents = false;

			if (meshRoot.contains("vertices")) {
				for (size_t i = 0; i < meshRoot["vertices"].size(); i++) {
					const JSON::Node& vertexNode = meshRoot["vertices"][i];

					Vertex vertex;
					if (vertexNode.contains("position")) {
						vertex.position = { vertexNode["position"][0].getNumber(), vertexNode["position"][1].getNumber(), vertexNode["position"][2].getNumber() };
					}

					if (vertexNode.contains("normal")) {
						vertex.normal = { vertexNode["normal"][0].getNumber(), vertexNode["normal"][1].getNumber(), vertexNode["normal"][2].getNumber() };
						hasNormals = true;
					}

					if (vertexNode.contains("uv")) {
						vertex.uv = { vertexNode["uv"][0].getNumber(), vertexNode["uv"][1].getNumber() };
						hasUvs = true;
					}

					if (vertexNode.contains("color")) {
						vertex.color = { vertexNode["color"][0].getNumber(), vertexNode["color"][1].getNumber(), vertexNode["color"][2].getNumber() };
					}

					if (vertexNode.contains("tangent")) {
						vertex.tangent = { vertexNode["tangent"][0].getNumber(), vertexNode["tangent"][1].getNumber(), vertexNode["tangent"][2].getNumber(), vertexNode["tangent"][3].getNumber() };
						hasTangents = true;
					}

					if (vertexNode.contains("joints")) {
						vertex.joints = std::array<uint32_t, 4>({ static_cast<uint32_t>(vertexNode["joints"][0].getNumber()), static_cast<uint32_t>(vertexNode["joints"][1].getNumber()), static_cast<uint32_t>(vertexNode["joints"][2].getNumber()), static_cast<uint32_t>(vertexNode["joints"][3].getNumber()) });
					}

					if (vertexNode.contains("weights")) {
						vertex.weights = { vertexNode["weights"][0].getNumber(), vertexNode["weights"][1].getNumber(), vertexNode["weights"][2].getNumber(), vertexNode["weights"][3].getNumber() };
					}

					mesh.vertices.push_back(vertex);
				}
			}

			if (meshRoot.contains("indices")) {
				for (size_t i = 0; i < meshRoot["indices"].size(); i++) {
					mesh.indices.push_back(static_cast<uint32_t>(meshRoot["indices"][i].getNumber()));
				}
				hasIndices = true;
			}

			// Calculate tangents
			if ((!hasTangents) && (hasNormals && hasUvs && hasIndices)) {
				calculateTangents(mesh);
			}

			if (meshRoot.contains("topology")) {
				mesh.topology = stringToMeshTopology.at(meshRoot["topology"].getString());
			}
		}

		void loadImageSamplerNtsp(const std::string& filePath, ImageSampler& imageSampler) {
			const std::unordered_map<std::string, ImageSamplerFilter> stringToImageSamplerFilter{
				{ "Linear", ImageSamplerFilter::Linear },
				{ "Nearest", ImageSamplerFilter::Nearest },
				{ "Unknown", ImageSamplerFilter::Unknown }
			};
			const std::unordered_map<std::string, ImageSamplerAddressMode> stringToImageSamplerAddressMode{
				{ "Repeat", ImageSamplerAddressMode::Repeat },
				{ "MirroredRepeat", ImageSamplerAddressMode::MirroredRepeat },
				{ "ClampToEdge", ImageSamplerAddressMode::ClampToEdge },
				{ "ClampToBorder", ImageSamplerAddressMode::ClampToBorder },
				{ "Unknown", ImageSamplerAddressMode::Unknown }
			};
			const std::unordered_map<std::string, ImageSamplerBorderColor> stringToImageSamplerBorderColor{
				{ "FloatTransparentBlack", ImageSamplerBorderColor::FloatTransparentBlack },
				{ "IntTransparentBlack", ImageSamplerBorderColor::IntTransparentBlack },
				{ "FloatOpaqueBlack", ImageSamplerBorderColor::FloatOpaqueBlack },
				{ "IntOpaqueBlack", ImageSamplerBorderColor::IntOpaqueBlack },
				{ "FloatOpaqueWhite", ImageSamplerBorderColor::FloatOpaqueWhite },
				{ "IntOpaqueWhite", ImageSamplerBorderColor::IntOpaqueWhite },
				{ "Unknown", ImageSamplerBorderColor::Unknown }
			};

			JSON json;
			const JSON::Node& imageSamplerRoot = json.read(filePath);

			if (imageSamplerRoot.contains("magFilter")) {
				imageSampler.magFilter = stringToImageSamplerFilter.at(imageSamplerRoot["magFilter"].getString());
			}

			if (imageSamplerRoot.contains("minFilter")) {
				imageSampler.minFilter = stringToImageSamplerFilter.at(imageSamplerRoot["minFilter"].getString());
			}

			if (imageSamplerRoot.contains("mipmapFilter")) {
				imageSampler.mipmapFilter = stringToImageSamplerFilter.at(imageSamplerRoot["mipmapFilter"].getString());
			}

			if (imageSamplerRoot.contains("addressModeU")) {
				imageSampler.addressModeU = stringToImageSamplerAddressMode.at(imageSamplerRoot["addressModeU"].getString());
			}

			if (imageSamplerRoot.contains("addressModeV")) {
				imageSampler.addressModeV = stringToImageSamplerAddressMode.at(imageSamplerRoot["addressModeV"].getString());
			}

			if (imageSamplerRoot.contains("addressModeW")) {
				imageSampler.addressModeW = stringToImageSamplerAddressMode.at(imageSamplerRoot["addressModeW"].getString());
			}

			if (imageSamplerRoot.contains("borderColor")) {
				imageSampler.borderColor = stringToImageSamplerBorderColor.at(imageSamplerRoot["borderColor"].getString());
			}

			if (imageSamplerRoot.contains("anisotropyLevel")) {
				imageSampler.anisotropyLevel = imageSamplerRoot["anisotropyLevel"].getNumber();
			}
		}

		void loadMaterialNtml(const std::string& filePath, Material& material) {
			JSON json;
			const JSON::Node& materialRoot = json.read(filePath);

			if (materialRoot.contains("diffuseTexture")) {
				const JSON::Node& diffuseTextureNode = materialRoot["diffuseTexture"];

				if (diffuseTextureNode.contains("imagePath")) {
					material.diffuseTexture.image = loadImage(diffuseTextureNode["imagePath"].getString());
				}

				if (diffuseTextureNode.contains("imageSamplerPath")) {
					loadImageSamplerNtsp(diffuseTextureNode["imageSamplerPath"].getString(), material.diffuseTexture.imageSampler);
				}
			}

			if (materialRoot.contains("normalTexture")) {
				const JSON::Node& normalTextureNode = materialRoot["normalTexture"];

				if (normalTextureNode.contains("imagePath")) {
					material.normalTexture.image = loadImage(normalTextureNode["imagePath"].getString());
				}

				if (normalTextureNode.contains("imageSamplerPath")) {
					loadImageSamplerNtsp(normalTextureNode["imageSamplerPath"].getString(), material.normalTexture.imageSampler);
				}
			}

			if (materialRoot.contains("metalnessTexture")) {
				const JSON::Node& metalnessTextureNode = materialRoot["metalnessTexture"];

				if (metalnessTextureNode.contains("imagePath")) {
					material.metalnessTexture.image = loadImage(metalnessTextureNode["imagePath"].getString());
				}

				if (metalnessTextureNode.contains("imageSamplerPath")) {
					loadImageSamplerNtsp(metalnessTextureNode["imageSamplerPath"].getString(), material.metalnessTexture.imageSampler);
				}
			}

			if (materialRoot.contains("roughnessTexture")) {
				const JSON::Node& roughnessTextureNode = materialRoot["roughnessTexture"];

				if (roughnessTextureNode.contains("imagePath")) {
					material.roughnessTexture.image = loadImage(roughnessTextureNode["imagePath"].getString());
				}

				if (roughnessTextureNode.contains("imageSamplerPath")) {
					loadImageSamplerNtsp(roughnessTextureNode["imageSamplerPath"].getString(), material.roughnessTexture.imageSampler);
				}
			}

			if (materialRoot.contains("occlusionTexture")) {
				const JSON::Node& occlusionTextureNode = materialRoot["occlusionTexture"];

				if (occlusionTextureNode.contains("imagePath")) {
					material.occlusionTexture.image = loadImage(occlusionTextureNode["imagePath"].getString());
				}

				if (occlusionTextureNode.contains("imageSamplerPath")) {
					loadImageSamplerNtsp(occlusionTextureNode["imageSamplerPath"].getString(), material.occlusionTexture.imageSampler);
				}
			}

			if (materialRoot.contains("emissiveTexture")) {
				const JSON::Node& emissiveTextureNode = materialRoot["emissiveTexture"];

				if (emissiveTextureNode.contains("imagePath")) {
					material.emissiveTexture.image = loadImage(emissiveTextureNode["imagePath"].getString());
				}

				if (emissiveTextureNode.contains("imageSamplerPath")) {
					loadImageSamplerNtsp(emissiveTextureNode["imageSamplerPath"].getString(), material.emissiveTexture.imageSampler);
				}
			}

			if (materialRoot.contains("emissiveFactor")) {
				material.emissiveFactor = materialRoot["emissiveFactor"].getNumber();
			}

			if (materialRoot.contains("alphaCutoff")) {
				material.alphaCutoff = materialRoot["alphaCutoff"].getNumber();
			}

			if (materialRoot.contains("indexOfRefraction")) {
				material.indexOfRefraction = materialRoot["indexOfRefraction"].getNumber();
			}
		}

		void loadModelNtmd(const std::string& filePath, Model& model) {
			JSON json;
			const JSON::Node& modelRoot = json.read(filePath);

			if (modelRoot.contains("primitives")) {
				for (size_t i = 0; i < modelRoot["primitives"].size(); i++) {
					const JSON::Node& primitiveNode = modelRoot["primitives"][i];

					ModelPrimitive primitive;
					if (primitiveNode.contains("meshPath")) {
						loadMeshNtmh(primitiveNode["meshPath"].getString(), primitive.mesh);
					}
					
					if (primitiveNode.contains("materialPath")) {
						loadMaterialNtml(primitiveNode["materialPath"].getString(), primitive.material);
					}

					model.primitives.push_back(primitive);
				}
			}
		}

		void loadImageNtim(const std::string& filePath, Image& image) {
			const std::unordered_map<std::string, ImageFormat> stringToImageFormat{
				{ "R8", ImageFormat::R8 },
				{ "R8G8", ImageFormat::R8G8 },
				{ "R8G8B8", ImageFormat::R8G8B8 },
				{ "R8G8B8A8", ImageFormat::R8G8B8A8 },
				{ "R16", ImageFormat::R16 },
				{ "R16G16", ImageFormat::R16G16 },
				{ "R16G16B16", ImageFormat::R16G16B16 },
				{ "R16G16B16A16", ImageFormat::R16G16B16A16 },
				{ "R32", ImageFormat::R32 },
				{ "R32G32", ImageFormat::R32G32 },
				{ "R32G32B32", ImageFormat::R32G32B32 },
				{ "R32G32B32A32", ImageFormat::R32G32B32A32 },
				{ "Unknown", ImageFormat::Unknown }
			};
			const std::unordered_map<std::string, ImageColorSpace> stringToImageColorSpace{
				{ "Linear", ImageColorSpace::Linear },
				{ "SRGB", ImageColorSpace::SRGB },
				{ "Unknown", ImageColorSpace::Unknown }
			};

			JSON json;
			const JSON::Node& imageRoot = json.read(filePath);

			if (imageRoot.contains("width")) {
				image.width = static_cast<uint32_t>(imageRoot["width"].getNumber());
			}
			if (imageRoot.contains("height")) {
				image.height = static_cast<uint32_t>(imageRoot["height"].getNumber());
			}
			if (imageRoot.contains("format")) {
				image.format = stringToImageFormat.at(imageRoot["format"].getString());
			}
			if (imageRoot.contains("colorSpace")) {
				image.colorSpace = stringToImageColorSpace.at(imageRoot["colorSpace"].getString());
			}
			if (imageRoot.contains("data")) {
				for (size_t i = 0; i < imageRoot["data"].size(); i++) {
					image.data.push_back(static_cast<uint8_t>(imageRoot["data"][i].getNumber()));
				}
			}
		}

	private:
		AssetLoaderModuleInterface* m_assetLoaderModule;

		std::forward_list<Sound> m_soundResources;
		std::forward_list<Model> m_modelResources;
		std::forward_list<Image> m_imageResources;
		std::forward_list<Font> m_fontResources;

		Bimap<std::string, Sound*> m_soundPaths;
		Bimap<std::string, Model*> m_modelPaths;
		Bimap<std::string, Image*> m_imagePaths;
		Bimap<std::string, Font*> m_fontPaths;
	};

}