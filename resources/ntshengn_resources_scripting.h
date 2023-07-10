#pragma once
#include <memory>

#define NTSHENGN_SCRIPT(scriptName) \
	protected: \
	scriptName* cloneImpl() { return new scriptName(*this); }

namespace NtshEngn {

	class GraphicsModuleInterface;
	class PhysicsModuleInterface;
	class WindowModuleInterface;
	class AudioModuleInterface;
	class ECS;
	class AssetManager;
	class FrameLimiter;
	class JobSystem;
	class Networking;
	using Entity = uint32_t;

	// Script
	struct Script {
		virtual ~Script() = default;

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		std::unique_ptr<Script> clone() { return std::unique_ptr<Script>(cloneImpl()); }
		void setEntityID(Entity passEntityID) { entityID = passEntityID; }
		void setSystemModules(GraphicsModuleInterface* passGraphicsModule, PhysicsModuleInterface* passPhysicsModule, WindowModuleInterface* passWindowModule, AudioModuleInterface* passAudioModule) {
			graphicsModule = passGraphicsModule;
			physicsModule = passPhysicsModule;
			windowModule = passWindowModule;
			audioModule = passAudioModule;
		}
		void setECS(ECS* passECS) { ecs = passECS; }
		void setAssetManager(AssetManager* passAssetManager) { assetManager = passAssetManager; }
		void setFrameLimiter(FrameLimiter* passFrameLimiter) { frameLimiter = passFrameLimiter; }
		void setJobSystem(JobSystem* passJobSystem) { jobSystem = passJobSystem; }
		void setNetworking(Networking* passNetworking) { networking = passNetworking; }

	protected:
		virtual Script* cloneImpl() = 0;

		Entity entityID = 0;

		GraphicsModuleInterface* graphicsModule = nullptr;
		PhysicsModuleInterface* physicsModule = nullptr;
		WindowModuleInterface* windowModule = nullptr;
		AudioModuleInterface* audioModule = nullptr;

		ECS* ecs = nullptr;

		AssetManager* assetManager = nullptr;

		FrameLimiter* frameLimiter = nullptr;

		JobSystem* jobSystem = nullptr;

		Networking* networking = nullptr;
	};

}