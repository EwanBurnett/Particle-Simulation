#pragma once
#include <cstdint>

// CONSTANTS

const uint64_t NUM_PARTICLES = 1 << 20; //How many particles to simulate at a time. 
const double TARGET_FRAMERATE = 1.0 / 60.0; //The target time to update all particles.
const uint64_t NUM_THREADS = 16u; //How many threads to launch
const uint64_t NUM_FRAMES = 1000u; //How many frames to simulate.
const bool SIMD_USE_SSE = true;
const bool SIMD_USE_AVX = true;
