#pragma once

typedef enum NtshResult {
	NTSH_RESULT_SUCCESS,
	NTSH_RESULT_ASSERT_FAILED,
	NTSH_RESULT_MODULE_LIBRARY_LOAD_ERROR,
	NTSH_RESULT_MODULE_SYMBOL_LOAD_ERROR,
	NTSH_RESULT_MODULE_FUNCTION_NOT_IMPLEMENTED,
	NTSH_RESULT_MODULE_ERROR,
	NTSH_RESULT_UNKNOWN_ERROR
} NtshResult;

typedef enum NtshModuleType {
	NTSH_MODULE_GRAPHICS,
	NTSH_MODULE_PHYSICS,
	NTSH_MODULE_WINDOW,
	NTSH_MODULE_AUDIO,
	NTSH_MODULE_UNKNOWN
} NtshModuleType;