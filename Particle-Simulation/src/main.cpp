//Particle Simulation
//Ewan Burnett - 2023
//
//A Simple 3D Particle Simulation, intended to practice C++ concurrency and parallelism techniques.

#include "../inc/Particle.h"
#include "../inc/Utility.h"
#include "../inc/Config.h"

#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

bool g_Start = false;
std::mutex g_Lock;
std::condition_variable g_CVStart;

// APPLICATION

void UpdateParticles(Particle* pParticles, uint64_t start, uint64_t end) {

	auto cvLock = std::unique_lock<std::mutex>(g_Lock);

	g_CVStart.wait(cvLock, [] {
		return g_Start;
	});

	for (size_t i = start; i < end; i++) {
        auto p = pParticles[i];
        p.position = p.position + (p.velocity * p.speed);
    }

}

int main()
{
	//Display information about what we're processing to the console
	printf("Particle Simulation\nEwan Burnett (2023)\n----------------------------\n\tNUM_PARTICLES: %lu\n\tMemory Consumption: %s\n\tNUM_THREADS: %d", NUM_PARTICLES, FormatBytes(NUM_PARTICLES * sizeof(Particle)).c_str(), NUM_THREADS);


	//Create the particles
	auto particles = new Particle[NUM_PARTICLES];

	//Initialize the threads
	std::vector<std::thread*> threads;
	for (size_t t = 0; t < NUM_THREADS; t++) {
		auto work = NUM_PARTICLES / NUM_THREADS;
		auto range = work * t;
		threads.push_back(new std::thread(UpdateParticles, particles, range, work + range));
	}

	{
		auto a = Timer("Single Pass");
		printf("\nProcessing Particles...");

		//Signal to all condition variables to start processing. 
		g_Start = true;
		g_CVStart.notify_all();

		for (auto t : threads) {
			t->join();
			delete(t);
		}

		printf("\nFinished Processing Particles.");
	}
	auto esc = getchar();

	// Cleanup
	delete[](particles);

	return 0;
}
