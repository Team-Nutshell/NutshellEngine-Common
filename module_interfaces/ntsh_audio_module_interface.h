#pragma once
#include "ntsh_module_interface.h"
#include "../resources/ntsh_resources_audio.h"

typedef uint64_t NtshAudioId;

class NutshellAudioModuleInterface : public NutshellModuleInterface {
public:
	NutshellAudioModuleInterface() {}
	NutshellAudioModuleInterface(const std::string& name) : NutshellModuleInterface(NtshModuleType::Audio, name) {}
	virtual ~NutshellAudioModuleInterface() {}

	virtual void init() = 0;
	virtual void update(double dt) = 0;
	virtual void destroy() = 0;

	// Loads the sound described in the audio parameter in the internal format and returns a unique identifier
	virtual NtshAudioId load(const NtshAudio audio) = 0;

	// Plays the audio with identifier audioId
	virtual void play(NtshAudioId audioId) = 0;
	// Pauses the audio with identifier audioId
	virtual void pause(NtshAudioId audioId) = 0;
	// Stops the audio with identifier audioId
	virtual void stop(NtshAudioId audioId) = 0;

	// Returns true if the audio with identifier audioId is currently playing, else, returns false
	virtual bool isPlaying(NtshAudioId audioId) = 0;

	// Sets the gain of the audio with identifier audioId
	virtual void setGain(NtshAudioId audioId, float newGain) = 0;
	// Gets the gain of the audio with identifier audioId
	virtual float getGain(NtshAudioId audioId) = 0;

	// Sets the pitch of the audio with identifier audioId
	virtual void setPitch(NtshAudioId audioId, float newPitch) = 0;
	// Gets the pitch of the audio with identifier audioId
	virtual float getPitch(NtshAudioId audioId) = 0;
};