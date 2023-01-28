#pragma once
#include "../utils/ntshengn_enums.h"
#include "../ecs/ntshengn_ecs.h"
#include <string>

namespace NtshEngn {

	class GraphicsModuleInterface;
	class PhysicsModuleInterface;
	class WindowModuleInterface;
	class AudioModuleInterface;
	class AssetManager;

	class ModuleInterface : public System {
	protected:
		ModuleType m_type = ModuleType::Unknown;
		std::string m_name = "";

		GraphicsModuleInterface* m_graphicsModule = nullptr;
		PhysicsModuleInterface* m_physicsModule = nullptr;
		WindowModuleInterface* m_windowModule = nullptr;
		AudioModuleInterface* m_audioModule = nullptr;

		ECS* m_ecs = nullptr;

		AssetManager* m_assetManager = nullptr;
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

		void setModules(GraphicsModuleInterface* graphicsModule, PhysicsModuleInterface* physicsModule, WindowModuleInterface* windowModule, AudioModuleInterface* audioModule) {
			m_graphicsModule = graphicsModule;
			m_physicsModule = physicsModule;
			m_windowModule = windowModule;
			m_audioModule = audioModule;
		}

		void setECS(ECS* ecs) {
			m_ecs = ecs;
		}

		void setAssetManager(AssetManager* assetManager) {
			m_assetManager = assetManager;
		}
	};

}