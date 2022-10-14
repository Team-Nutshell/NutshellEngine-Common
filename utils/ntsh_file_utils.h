#pragma once
#include <fstream>
#include <string>
#include "../ntsh_engine_defines.h"

namespace utils {
	namespace file {
		static std::string readAscii(const std::string& filePath) {
			std::ifstream file(filePath, std::ios::in | std::ios::ate);
			if (!file.is_open()) {
				return "";
			}
			file.seekg(0);
			std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			return fileContent;
		}

		static std::string readBinary(const std::string& filePath) {
			std::ifstream file(filePath, std::ios::in | std::ios::ate | std::ios::binary);
			if (!file.is_open()) {
				return "";
			}
			file.seekg(0);
			std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			return fileContent;
		}

		static std::string filename(const std::string& filePath) {
			size_t slashPosition = filePath.find_last_of('/');
			if (slashPosition == std::string::npos) {
				slashPosition = filePath.find_last_of('\\');
				if (slashPosition == std::string::npos) {
					return filePath;
				}
			}
			return filePath.substr(slashPosition + 1);
		}

		static std::string extension(const std::string& filePath) {
			size_t dotPosition = filePath.find_last_of('.');
			if (dotPosition == std::string::npos) {
				return "";
			}
			return filePath.substr(dotPosition + 1);
		}

		static bool exists (const std::string& filePath) {
			std::ifstream file(filePath);
			return file.good();
		}
	}
}