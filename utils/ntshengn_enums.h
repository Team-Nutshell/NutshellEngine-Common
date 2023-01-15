#pragma once

namespace NtshEngn {

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