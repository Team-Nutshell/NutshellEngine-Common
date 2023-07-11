#pragma once

namespace NtshEngn {

	enum class Result {
		Success,
		AssertFailed,
		ModuleLibraryLoadError,
		ModuleSymbolLoadError,
		ModuleFunctionNotImplemented,
		ModuleError,
		AssetManagerFileNotFound,
		AssetManagerError,
		UnknownError
	};

	enum class ModuleType {
		Graphics,
		Physics,
		Window,
		Audio,
		AssetLoader,
		Unknown
	};

}