#pragma once
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
		position = {};
		velocity = {};
		speed = 5.0f;
		size = 1.0f;
	}

	Vector3 position;
	Vector3 velocity;
	float speed;
	float size;
};


