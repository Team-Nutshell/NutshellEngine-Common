#pragma once
#include <string>

namespace utils {
	namespace file {
		static std::string readAscii(const std::string& filePath);
		static std::string readBinary(const std::string& filePath);
		static std::string filename(const std::string& filePath);
		static std::string extension(const std::string& filePath);
		static bool exists (const std::string& filePath);
	}
}