#pragma once
// CONSTANTS

const uint64_t NUM_PARTICLES = 1 << 25; //How many particles to simulate at a time. 
const double TARGET_FRAMERATE = 1.0 / 60.0; //The target time to update all particles.
const uint64_t NUM_THREADS = 16u;//How many threads to launch

