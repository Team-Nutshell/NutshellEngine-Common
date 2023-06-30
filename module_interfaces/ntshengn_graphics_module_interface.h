#pragma once
#include "ntshengn_module_interface.h"
#include "../resources/ntshengn_resources_graphics.h"

namespace NtshEngn {

	class GraphicsModuleInterface : public ModuleInterface {
	public:
		GraphicsModuleInterface() {}
		GraphicsModuleInterface(const std::string& name) : ModuleInterface(ModuleType::Graphics, name) {}
		virtual ~GraphicsModuleInterface() {}

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		// Loads the mesh described in the mesh parameter in the internal format and returns a unique identifier
		virtual MeshID load(const Mesh& mesh) = 0;
		// Loads the image described in the image parameter in the internal format and returns a unique identifier
		virtual ImageID load(const Image& image) = 0;
	};

}