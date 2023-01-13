#pragma once
#include "ntsh_module_interface.h"
#include "../resources/ntsh_resources_audio.h"

class NutshellAudioModuleInterface : public NutshellModuleInterface {
public:
	NutshellAudioModuleInterface() {}
	NutshellAudioModuleInterface(const std::string& name) : NutshellModuleInterface(Ntsh::ModuleType::Audio, name) {}
	virtual ~NutshellAudioModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;

	// Loads the sound described in the sound parameter in the internal format and returns a unique identifier
	virtual Ntsh::SoundId load(const Ntsh::Sound sound) = 0;

	// Plays the sound with identifier soundId
	virtual void play(Ntsh::SoundId soundId) = 0;
	// Pauses the sound with identifier soundId
	virtual void pause(Ntsh::SoundId soundId) = 0;
	// Stops the sound with identifier soundId
	virtual void stop(Ntsh::SoundId soundId) = 0;

	// Returns true if the sound with identifier soundId is currently playing, else, returns false
	virtual bool isPlaying(Ntsh::SoundId soundId) = 0;

	// Sets the gain of the sound with identifier soundId
	virtual void setGain(Ntsh::SoundId soundId, float newGain) = 0;
	// Gets the gain of the sound with identifier soundId
	virtual float getGain(Ntsh::SoundId soundId) = 0;

	// Sets the pitch of the sound with identifier soundId
	virtual void setPitch(Ntsh::SoundId soundId, float newPitch) = 0;
	// Gets the pitch of the sound with identifier soundId
	virtual float getPitch(Ntsh::SoundId soundId) = 0;
};