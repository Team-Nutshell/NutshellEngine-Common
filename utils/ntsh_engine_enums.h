#pragma once

namespace Ntsh {

enum class Result {
	Success,
	AssertFailed,
	ModuleLibraryLoadError,
	ModuleSymbolLoadError,
	ModuleFunctionNotImplemented,
	ModuleError,
	AssetLoaderFileNotFound,
	AssetLoaderError,
	UnknownError
};

enum class ModuleType {
	Graphics,
	Physics,
	Window,
	Audio,
	Unknown
};

}