#pragma once
#include <cstdint>

// Image
typedef enum NtshImageFormat {
	NTSH_IMAGE_FORMAT_R8;
	NTSH_IMAGE_FORMAT_R8G8;
	NTSH_IMAGE_FORMAT_R8G8B8;
	NTSH_IMAGE_FORMAT_R8G8B8A8;
	NTSH_IMAGE_FORMAT_R16;
	NTSH_IMAGE_FORMAT_R16G16;
	NTSH_IMAGE_FORMAT_R16G16B16;
	NTSH_IMAGE_FORMAT_R16G16B16A16;
	NTSH_IMAGE_FORMAT_R32;
	NTSH_IMAGE_FORMAT_R32G32;
	NTSH_IMAGE_FORMAT_R32G32B32;
	NTSH_IMAGE_FORMAT_R32G32B32A32;
} NtshImageFormat;

struct NtshImage {
	// Image width
	uint32_t width;
	
	// Image height
	uint32_t height;

	// Image format
	NtshImageFormat format;

	// Data, size can be calculated from width, height and format
	uint8_t* pData;
};

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
	uint8_t* pData;
};