#pragma once
#include "../utils/ntshengn_enums.h"
#include "../ecs/ntshengn_ecs.h"
#include "../asset_manager/ntshengn_asset_manager.h"
#include <string>

namespace NtshEngn {

	class GraphicsModuleInterface;
	class PhysicsModuleInterface;
	class WindowModuleInterface;
	class AudioModuleInterface;

	class ModuleInterface : public System {
	public:
		ModuleInterface() {}
		ModuleInterface(const ModuleType type, const std::string& name) : m_type(type), m_name(name) {}
		virtual ~ModuleInterface() {}

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		const ModuleType getType() const {
			return m_type;
		}

		const std::string& getName() const {
			return m_name;
		}

		virtual const ComponentMask getComponentMask() const {
			return ComponentMask();
		}

		void setModules(GraphicsModuleInterface* passGraphicsModule, PhysicsModuleInterface* passPhysicsModule, WindowModuleInterface* passWindowModule, AudioModuleInterface* passAudioModule) {
			graphicsModule = passGraphicsModule;
			physicsModule = passPhysicsModule;
			windowModule = passWindowModule;
			audioModule = passAudioModule;
		}

		void setECS(ECS* passECS) {
			ecs = passECS;
		}

		void setAssetManager(AssetManager* passAssetManager) {
			assetManager = passAssetManager;
		}
		
	protected:
		GraphicsModuleInterface* graphicsModule = nullptr;
		PhysicsModuleInterface* physicsModule = nullptr;
		WindowModuleInterface* windowModule = nullptr;
		AudioModuleInterface* audioModule = nullptr;

		ECS* ecs = nullptr;

		AssetManager* assetManager = nullptr;

	private:
		
		ModuleType m_type = ModuleType::Unknown;
		std::string m_name = "";
	};

}