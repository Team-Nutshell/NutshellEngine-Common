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
	using Entity = int32_t;

	// Script
	struct Script {
		virtual ~Script() = default;

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		std::unique_ptr<Script> clone() { return std::unique_ptr<Script>(clone_impl()); }
		void setEntityID(Entity entityID) { m_entityID = entityID; }
		void setModules(GraphicsModuleInterface* graphicsModule, PhysicsModuleInterface* physicsModule, WindowModuleInterface* windowModule, AudioModuleInterface* audioModule) {
			m_graphicsModule = graphicsModule;
			m_physicsModule = physicsModule;
			m_windowModule = windowModule;
			m_audioModule = audioModule;
		}
		void setECS(ECS* ecs) { m_ecs = ecs; }
	protected:
		virtual Script* clone_impl() = 0;

		Entity m_entityID = 0;

		GraphicsModuleInterface* m_graphicsModule = nullptr;
		PhysicsModuleInterface* m_physicsModule = nullptr;
		WindowModuleInterface* m_windowModule = nullptr;
		AudioModuleInterface* m_audioModule = nullptr;

		ECS* m_ecs = nullptr;
	};

}