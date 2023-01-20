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
		virtual SoundId load(const Sound& sound) = 0;

		// Plays the sound with identifier soundId
		virtual void play(SoundId soundId) = 0;
		// Pauses the sound with identifier soundId
		virtual void pause(SoundId soundId) = 0;
		// Stops the sound with identifier soundId
		virtual void stop(SoundId soundId) = 0;

		// Returns true if the sound with identifier soundId is currently playing, else, returns false
		virtual bool isPlaying(SoundId soundId) = 0;

		// Sets the gain of the sound with identifier soundId
		virtual void setGain(SoundId soundId, float newGain) = 0;
		// Gets the gain of the sound with identifier soundId
		virtual float getGain(SoundId soundId) = 0;

		// Sets the pitch of the sound with identifier soundId
		virtual void setPitch(SoundId soundId, float newPitch) = 0;
		// Gets the pitch of the sound with identifier soundId
		virtual float getPitch(SoundId soundId) = 0;
	};

}