#pragma once
#include "Config.h"

// PARTICLES

struct Vector3 {
	Vector3() {
		//Zero out each component
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	float x, y, z;

	Vector3& operator + (const Vector3& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}

	Vector3& operator * (const float& rhs) {
		x *= rhs;
		y *= rhs;
		z *= rhs;

		return *this;
	}
};

//AoS Particle structure
struct Particle {
	Particle() {
		positions = new Vector3[NUM_PARTICLES];
		velocities = new Vector3[NUM_PARTICLES];
		speeds = new float[NUM_PARTICLES];
		sizes = new float[NUM_PARTICLES];
	}

	~Particle() {
		delete[] positions;
		delete[] velocities;
		delete[] speeds;
		delete[] sizes;
	}

	alignas(16) Vector3* positions;
	alignas(16) Vector3* velocities;
	alignas(16) float* speeds;
	alignas(16) float* sizes;
};


