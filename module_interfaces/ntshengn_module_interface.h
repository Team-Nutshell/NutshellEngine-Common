#pragma once
#include "../utils/ntshengn_enums.h"
#include <string>

namespace NtshEngn {

	class ModuleInterface {
	public:
		ModuleInterface() {}
		ModuleInterface(const ModuleType type, const std::string& name) : m_type(type), m_name(name) {}
		virtual ~ModuleInterface() {}

		const ModuleType getType() const {
			return m_type;
		}

		const std::string& getName() const {
			return m_name;
		}

	private:
		ModuleType m_type = ModuleType::Unknown;
		std::string m_name = "";
	};

}