#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>

// Audio
struct NtshAudio {
	// Number of channels (1 = Mono, 2 = Stereo, ...)
	uint8_t channels;

	// Sample rate
	int32_t sampleRate;

	// Number of bits per sample
	uint8_t bitsPerSample;

	// Size of the data
	size_t size;

	// Data
	std::vector<uint8_t> data;
};