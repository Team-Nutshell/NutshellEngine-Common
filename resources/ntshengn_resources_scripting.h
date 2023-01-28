#pragma once

#define NTSHENGN_SCRIPT(scriptName) \
	protected: \
	scriptName* clone_impl() { return new scriptName(*this); }

namespace NtshEngn {

	class GraphicsModuleInterface;
	class PhysicsModuleInterface;
	class WindowModuleInterface;
	class AudioModuleInterface;
	class ECS;
	class AssetManager;
	using Entity = uint32_t;

	// Script
	struct Script {
		virtual ~Script() = default;

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		std::unique_ptr<Script> clone() { return std::unique_ptr<Script>(clone_impl()); }
		void setEntityID(Entity passEntityID) { entityID = passEntityID; }
		void setModules(GraphicsModuleInterface* passGraphicsModule, PhysicsModuleInterface* passPhysicsModule, WindowModuleInterface* passWindowModule, AudioModuleInterface* passAudioModule) {
			graphicsModule = passGraphicsModule;
			physicsModule = passPhysicsModule;
			windowModule = passWindowModule;
			audioModule = passAudioModule;
		}
		void setECS(ECS* passECS) { ecs = passECS; }
		void setAssetManager(AssetManager* passAssetManager) { assetManager = passAssetManager; }
	protected:
		virtual Script* clone_impl() = 0;

		Entity entityID = 0;

		GraphicsModuleInterface* graphicsModule = nullptr;
		PhysicsModuleInterface* physicsModule = nullptr;
		WindowModuleInterface* windowModule = nullptr;
		AudioModuleInterface* audioModule = nullptr;

		ECS* ecs = nullptr;

		AssetManager* assetManager = nullptr;
	};

}