#pragma once
#include "ntsh_module_interface.h"
#include "../resources/ntsh_resources_graphics.h"

class NutshellGraphicsModuleInterface : public NutshellModuleInterface {
public:
	NutshellGraphicsModuleInterface() {}
	NutshellGraphicsModuleInterface(const std::string& name) : NutshellModuleInterface(NtshModuleType::Graphics, name) {}
	virtual ~NutshellGraphicsModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;

	// Loads the mesh described in the mesh parameter in the internal format and returns a unique identifier
	virtual Ntsh::MeshId load(const Ntsh::Mesh mesh) = 0;
	// Loads the image described in the image parameter in the internal format and returns a unique identifier
	virtual Ntsh::ImageId load(const Ntsh::Image image) = 0;
};