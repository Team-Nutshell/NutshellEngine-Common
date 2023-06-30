#pragma once
#include "ntshengn_module_interface.h"
#include "../resources/ntshengn_resources_audio.h"

namespace NtshEngn {

	class AudioModuleInterface : public ModuleInterface {
	public:
		AudioModuleInterface() {}
		AudioModuleInterface(const std::string& name) : ModuleInterface(ModuleType::Audio, name) {}
		virtual ~AudioModuleInterface() {}

		virtual void init() = 0;
		virtual void update(double dt) = 0;
		virtual void destroy() = 0;

		// Loads the sound described in the sound parameter in the internal format and returns a unique identifier
		virtual SoundID load(const Sound& sound) = 0;

		// Plays the sound with identifier soundID
		virtual void play(SoundID soundID) = 0;
		// Pauses the sound with identifier soundID
		virtual void pause(SoundID soundID) = 0;
		// Stops the sound with identifier soundID
		virtual void stop(SoundID soundID) = 0;

		// Returns true if the sound with identifier soundID is currently playing, else, returns false
		virtual bool isPlaying(SoundID soundID) = 0;

		// Sets the gain of the sound with identifier soundID
		virtual void setGain(SoundID soundID, float newGain) = 0;
		// Gets the gain of the sound with identifier soundID
		virtual float getGain(SoundID soundID) = 0;

		// Sets the pitch of the sound with identifier soundID
		virtual void setPitch(SoundID soundID, float newPitch) = 0;
		// Gets the pitch of the sound with identifier soundID
		virtual float getPitch(SoundID soundID) = 0;
	};

}