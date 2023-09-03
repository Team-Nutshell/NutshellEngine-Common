#pragma once
#include <memory>

#define NTSHENGN_SCRIPT(scriptName) \
	protected: \
		scriptName* cloneImpl() { return new scriptName(*this); }

namespace NtshEngn {

	// Script
	struct ScriptBase {
		virtual ~ScriptBase() = default;

		std::unique_ptr<ScriptBase> clone() { return std::unique_ptr<ScriptBase>(cloneImpl()); }

	protected:
		virtual ScriptBase* cloneImpl() = 0;
	};

}