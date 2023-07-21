#pragma once
#include "../../resources/ntshengn_resources_scripting.h"
#include <memory>

namespace NtshEngn {

	struct Scriptable {
		Scriptable() = default;
		~Scriptable() = default;
		Scriptable(const Scriptable& other) : script(other.script->clone()) {}
		Scriptable(Scriptable&& other) = default;
		Scriptable& operator=(const Scriptable& other) { script = other.script->clone(); return *this; }
		Scriptable& operator=(Scriptable&& other) = default;

		std::unique_ptr<Script> script = nullptr;
	};

}