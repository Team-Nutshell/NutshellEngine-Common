#pragma once
#include "ntsh_engine_enums.h"
#include <iostream>

#define NTSH_UNUSED(expression) \
	do { \
		(void)(expression); \
	} while(0)

#if defined(NTSH_DEBUG)
#define NTSH_ASSERT(expression) \
	do { \
		if (!(expression)) { \
			std::cerr << "\33[1m\33[31mASSERTION FAILED\33[39m\33[0m: " << #expression << ".\nLine \33[1m" << __LINE__ << "\33[0m in file \33[1m" << __FILE__ << "\33[0m." << std::endl; \
			exit(1); \
		} \
	} while(0)
#else
#define NTSH_ASSERT(expression) \
	do { \
	} while(0)
#endif

#define NTSH_POINTER_EXECUTE(pointer, function) \
	do { \
		if (pointer) { \
			pointer->function; \
		} \
	} while(0)
	