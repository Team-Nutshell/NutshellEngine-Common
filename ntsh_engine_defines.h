#include <iostream>

#define NTSH_UNUSED(expression) \
	do { \
		(void)(expression); \
	} while(0)

#ifndef NDEBUG
#define NTSH_ASSERT(expression) \
	do { \
		if (!expression) { \
			std::cerr << "\33[1m\33[31mASSERTION FAILED: " << #expression << " failed on line " << __LINE__ << " in file " << __FILE__ << "." << std::endl; \
		} \
	} while(0)
#else
	do { \
	} while(0)
#endif