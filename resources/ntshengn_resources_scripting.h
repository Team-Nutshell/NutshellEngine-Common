#pragma once

#define NTSHENGN_SCRIPT(scriptName) \
	protected: \
	scriptName* clone_impl() { return new scriptName(*this); }

namespace NtshEngn {

	// Script
	struct Script {
		virtual ~Script() = default;

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		std::unique_ptr<Script> clone() { return std::unique_ptr<Script>(clone_impl()); }
	protected:
		virtual Script* clone_impl() = 0;
	};

}