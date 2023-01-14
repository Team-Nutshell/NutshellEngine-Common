#pragma once
#include "../ecs/ecs_includes.h"
#include <string>

class NutshellGraphicsModuleInterface;
class NutshellPhysicsModuleInterface;
class NutshellWindowModuleInterface;
class NutshellAudioModuleInterface;

class NutshellModuleInterface : public System {
protected:
	Ntsh::ModuleType m_type = Ntsh::ModuleType::Unknown;
	std::string m_name = "";

	NutshellGraphicsModuleInterface* m_graphicsModule = nullptr;
	NutshellPhysicsModuleInterface* m_physicsModule = nullptr;
	NutshellWindowModuleInterface* m_windowModule = nullptr;
	NutshellAudioModuleInterface* m_audioModule = nullptr;

	ECS* m_ecs;
public:
	NutshellModuleInterface() {}
	NutshellModuleInterface(const Ntsh::ModuleType type, const std::string& name) : m_type(type), m_name(name) {}
	virtual ~NutshellModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;

	const Ntsh::ModuleType getType() const {
		return m_type;
	}

	const std::string& getName() const {
		return m_name;
	}

	void setModules(NutshellGraphicsModuleInterface* graphicsModule, NutshellPhysicsModuleInterface* physicsModule, NutshellWindowModuleInterface* windowModule, NutshellAudioModuleInterface* audioModule) {
		m_graphicsModule = graphicsModule;
		m_physicsModule = physicsModule;
		m_windowModule = windowModule;
		m_audioModule = audioModule;
	}

	void setECS(ECS* ecs) {
		m_ecs = ecs;
	}
};