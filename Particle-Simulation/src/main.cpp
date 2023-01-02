//Particle Simulation
//Ewan Burnett - 2023
//
//A Simple 3D Particle Simulation, intended to practice C++ concurrency and parallelism techniques.

#include <cstdio>	//For Logging
#include <cstdint> 
#include <string>

//Application Constants
const uint64_t NUM_PARTICLES = 2000; //How many particles to simulate at a time. 


//PARTICLES

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

// UTILITY
//Outputs a formatted string, representing the number of bytes. (e.g. 4kb instead of 4096 bytes)
std::string FormatBytes(const uint64_t bytes) {
	std::string output;

	//If the size is less than 1024 (1kb), then output bytes.
	if (bytes < 1024u) {
		output.append(std::to_string(bytes));
		output.append("b");
	}
	//Otherwise, if the size is less than 1Mb, then output kilobytes.
	else if (bytes > 1024u && bytes < (1024 * 1024)) {
		float size = bytes / 1024.0f;
		output.append(std::to_string(size));
		output.append("kb");
	}
	//For any other size, output Megabytes.
	else {
		float size = bytes / 1024.0f / 1024.0f;
		output.append(std::to_string(size));
		output.append("Mb");
	}

	return output;
}

int main()
{
	//Display information about what we're processing to the console
	printf("Particle Simulation\nEwan Burnett (2023)\n----------------------------\n\tNUM_PARTICLES: %u\n\tMemory Consumption: %s", NUM_PARTICLES, FormatBytes(NUM_PARTICLES * sizeof(Particle)).c_str());

	//Create the particles
	auto particles = new Particle[NUM_PARTICLES];

	//Process each particle
	printf("\nProcessing Particles...");
    for (size_t i = 0; i < NUM_PARTICLES; i++) {
        auto p = particles[i];
        p.position = p.position + (p.velocity * p.speed);
    }
    printf("\nFinished Processing Particles.");
	auto esc = getchar();

	// Cleanup
	delete[](particles);

	return 0;
}
