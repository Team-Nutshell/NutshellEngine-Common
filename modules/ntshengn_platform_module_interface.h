#pragma once
#include "ntshengn_module_interface.h"
#include <cstdint>

namespace NtshEngn {

	class PlatformModuleInterface : public ModuleInterface {
	public:
		PlatformModuleInterface() {}
		PlatformModuleInterface(const std::string& name) : ModuleInterface(ModuleType::Platform, name) {}
		virtual ~PlatformModuleInterface() {}

		// Returns the user's ID on the platform
		virtual uint64_t getUserID() = 0;
		// Returns the user's name on the platform
		virtual std::string getUserName() = 0;

		// Show the platform's overlay
		virtual void showOverlay() = 0;
		// Returns true if the platform's overlay is visible
		virtual bool isOverlayVisible() = 0;
	};

}