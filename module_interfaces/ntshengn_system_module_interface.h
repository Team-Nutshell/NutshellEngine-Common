#pragma once
#include "ntshengn_module_interface.h"
#include "../ecs/ntshengn_ecs.h"
#include "../asset_manager/ntshengn_asset_manager.h"
#include "../job_system/ntshengn_job_system.h"
#include <string>

namespace NtshEngn {

	class GraphicsModuleInterface;
	class PhysicsModuleInterface;
	class WindowModuleInterface;
	class AudioModuleInterface;

	class SystemModuleInterface : public ModuleInterface, public System {
	public:
		SystemModuleInterface() {}
		SystemModuleInterface(const ModuleType type, const std::string& name) : ModuleInterface(type, name) {}
		virtual ~SystemModuleInterface() {}

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		virtual const ComponentMask getComponentMask() const {
			return ComponentMask();
		}

		void setSystemModules(GraphicsModuleInterface* passGraphicsModule, PhysicsModuleInterface* passPhysicsModule, WindowModuleInterface* passWindowModule, AudioModuleInterface* passAudioModule) {
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

		void setJobSystem(JobSystem* passJobSystem) {
			jobSystem = passJobSystem;
		}
		
	protected:
		GraphicsModuleInterface* graphicsModule = nullptr;
		PhysicsModuleInterface* physicsModule = nullptr;
		WindowModuleInterface* windowModule = nullptr;
		AudioModuleInterface* audioModule = nullptr;

		ECS* ecs = nullptr;

		AssetManager* assetManager = nullptr;

		JobSystem* jobSystem = nullptr;
	};

}