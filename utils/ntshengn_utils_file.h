#pragma once
#if defined(NTSHENGN_OS_LINUX) || defined(NTSHENGN_OS_FREEBSD)
#include <sys/stat.h>
#endif
#include <fstream>
#include <string>
#include <cstdio>

namespace NtshEngn {

	class File {
	public:
		static std::string readAscii(const std::string& filePath) {
			std::ifstream file(filePath, std::ios::in | std::ios::ate);
			if (!file.is_open()) {
				return "";
			}
			file.seekg(0);
			std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			
			return fileContent;
		}

		static std::wstring readUtf8(const std::string& filePath) {
			std::wstring utf8Data;

			std::string mode = "";
#if defined(NTSHENGN_OS_WINDOWS)
			mode = "rtS, ccs=UTF-8";
#elif defined(NTSHENGN_OS_LINUX) || defined(NTSHENGN_OS_FREEBSD)
			mode = "r";
#endif
			FILE* f = fopen(filePath.c_str(), mode.c_str());
			if (!f) {
				return L"";
			}

			struct stat fileInfo;
			stat(filePath.c_str(), &fileInfo);
			if (fileInfo.st_size > 0) {
				utf8Data.resize(fileInfo.st_size);
				size_t wcharRead = fread(&(utf8Data.front()), sizeof(wchar_t), fileInfo.st_size, f);
				utf8Data.resize(wcharRead);
				utf8Data.shrink_to_fit();
			}

			fclose(f);
			
			return utf8Data;
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

		static void writeAscii(const std::string& filePath, const std::string& content) {
			std::ofstream file(filePath, std::ios::out);
			file << content;
		}

		static void writeBinary(const std::string& filePath, const std::string& content) {
			std::ofstream file(filePath, std::ios::out | std::ios::binary);
			file << content;
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

		static std::string directory(const std::string& filePath) {
			size_t slashPosition = filePath.find_last_of('/');
			if (slashPosition == std::string::npos) {
				slashPosition = filePath.find_last_of('\\');
				if (slashPosition == std::string::npos) {
					return filePath;
				}
			}
			
			return filePath.substr(0, slashPosition + 1);
		}
	};

}