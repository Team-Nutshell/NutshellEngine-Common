#pragma once
#include <iostream>

#define NTSHENGN_UNUSED(expression) \
	do { \
		(void)(expression); \
	} while(0)

#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_ASSERT(expression) \
	do { \
		if (!(expression)) { \
			std::cerr << "\33[1m\33[31mASSERTION FAILED\33[39m\33[0m: " << #expression << ".\nLine \33[1m" << __LINE__ << "\33[0m in file \33[1m" << __FILE__ << "\33[0m." << std::endl; \
			exit(1); \
		} \
	} while(0)
#else
#define NTSHENGN_ASSERT(expression) \
	do { \
	} while(0)
#endif

#define NTSHENGN_POINTER_EXECUTE(pointer, function) \
	do { \
		if (pointer) { \
			pointer->function; \
		} \
	} while(0)
	
#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_ASSET_MANAGER_INFO(message) \
	do { \
		std::cerr << "\33[1m\33[94mASSET MANAGER \33[34mINFO\33[39m\33[0m: " << message << std::endl; \
	} while(0)
#else
#define NTSHENGN_ASSET_MANAGER_INFO(message) \
	do { \
	} while(0)
#endif

#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_ASSET_MANAGER_WARNING(message) \
	do { \
		std::cerr << "\33[1m\33[94mASSET MANAGER \33[93mWARNING\33[39m\33[0m: " << message << std::endl; \
	} while(0)
#else
#define NTSHENGN_ASSET_MANAGER_WARNING(message) \
	do { \
	} while(0)
#endif

#if defined(NTSHENGN_DEBUG)
#define NTSHENGN_ASSET_MANAGER_ERROR(message, code) \
	do { \
		std::cerr << "\33[1m\33[94mASSET MANAGER \33[31mERROR\33[39m\33[0m: " << message << " (" << #code << ")" << std::endl; \
		exit(1); \
	} while(0)
#else
#define NTSHENGN_ASSET_MANAGER_ERROR(message, code) \
	do { \
		exit(1); \
	} while(0)
#endif