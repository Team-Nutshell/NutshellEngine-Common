#pragma once

enum class NtshResult {
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

enum class NtshModuleType {
	Graphics,
	Physics,
	Window,
	Audio,
	Unknown
};