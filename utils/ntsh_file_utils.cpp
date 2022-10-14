#include "ntsh_file_utils.h"
#include <fstream>

namespace utils {
	namespace file {
		std::string readAscii(const std::string& filePath) {
			std::ifstream file(filePath, std::ios::in | std::ios::ate);
			if (!file.is_open()) {
				return "";
			}
			file.seekg(0);
			std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			return fileContent;
		}

		std::string readBinary(const std::string& filePath) {
			std::ifstream file(filePath, std::ios::in | std::ios::ate | std::ios::binary);
			if (!file.is_open()) {
				return "";
			}
			file.seekg(0);
			std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			return fileContent;
		}

		std::string filename(const std::string& filePath) {
			size_t slashPosition = filePath.find_last_of('/');
			if (slashPosition == std::string::npos) {
				slashPosition = filePath.find_last_of('\\');
				if (slashPosition == std::string::npos) {
					return filePath;
				}
			}
			return filePath.substr(slashPosition + 1);
		}

		std::string extension(const std::string& filePath) {
			size_t dotPosition = filePath.find_last_of('.');
			if (dotPosition == std::string::npos) {
				return "";
			}
			return filePath.substr(dotPosition + 1);
		}

		bool exists (const std::string& filePath) {
			std::ifstream file(filePath);
			return file.good();
		}
	}
}