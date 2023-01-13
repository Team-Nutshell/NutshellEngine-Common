#pragma once
#include "ntsh_engine_keyboard_enums.h"
#include "ntsh_engine_mouse_enums.h"

namespace Ntsh {

enum class InputState {
	None, // State when the input is neutral
	Pressed, // State on the frame an input is pressed
	Held, // State after an input is pressed and before it's released
	Released // State on the frame an input is released
};

}