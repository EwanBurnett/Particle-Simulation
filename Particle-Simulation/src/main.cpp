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
#include <barrier>

#include <immintrin.h>

bool g_Start = false;
std::mutex g_Lock;
std::condition_variable g_CVStart;
std::barrier g_FrameSync(NUM_THREADS, []() noexcept {
	printf("\nFinished Update");
    //Draw
    //std::this_thread::sleep_for(std::chrono::milliseconds(10));
	printf("\tFinished Draw");
});

// APPLICATION

void UpdateParticles(Particle* pParticles, uint64_t start, uint64_t end) {

	while (!g_Start) //Poll whether the condition variable has been signalled like this, in case of spurious wakeups.
	{
		std::unique_lock<std::mutex> cvLock(g_Lock);

		g_CVStart.wait(cvLock, [] {
			return g_Start;
			});
	}

	for (int f = 0; f < NUM_FRAMES; f++) {
		//Critical Section - Update each particle
		//Position += velocity * speed * dt

		//Update based on SIMD mode
		if (SIMD_USE_AVX) { //Update with 8-lane AVX intrinsics
            __m256* pPos = (__m256*)pParticles->positions;
			__m256* pVel = (__m256*)pParticles->positions;
			__m256* pSpd = (__m256*)pParticles->positions;

			for (size_t i = start; i < end; i += (sizeof(__m256) / sizeof(float))) {

				*pPos = _mm256_add_ps(*pPos, _mm256_mul_ps(*pVel, *pSpd));

				pPos++;
				pVel++;
				pSpd++;
			}

		}
		else if (SIMD_USE_SSE) { //Update with 4-lane SSE intrinsics
			__m128* pPos = (__m128*)pParticles->positions;
			__m128* pVel = (__m128*)pParticles->positions;
			__m128* pSpd = (__m128*)pParticles->positions;

			for (size_t i = start; i < end; i += (sizeof(__m128) / sizeof(float))) {

				*pPos = _mm_add_ps(*pPos, _mm_mul_ps(*pVel, *pSpd));

				pPos++;
				pVel++;
				pSpd++;
			}
		}
		else { //Update without SIMD
            for (size_t i = start; i < end; i++) {
                auto& pos = pParticles->positions[i];
				auto vel = pParticles->velocities[i];
				auto spd = pParticles->speeds[i];
                pos = pos + (vel * spd);
            }
		}
		g_FrameSync.arrive_and_wait();
	}

}

int main()
{
	//Display information about what we're processing to the console
	printf("Particle Simulation\nEwan Burnett (2023)\n----------------------------\n\tNUM_PARTICLES: %lu\n\tMemory Consumption: %s\n\tNUM_THREADS: %d\n\tNUM_FRAMES: %lu", NUM_PARTICLES, FormatBytes(NUM_PARTICLES * sizeof(Particle)).c_str(), NUM_THREADS, NUM_FRAMES);


	//Create the particles
	Particle particles;

	//Initialize the threads
	std::vector<std::thread*> threads;
	for (size_t t = 0; t < NUM_THREADS; t++) {
		auto work = NUM_PARTICLES / NUM_THREADS;
		auto range = work * t;
		threads.push_back(new std::thread(UpdateParticles, &particles, range, work + range));
	}

	{
		auto a = Timer(std::to_string(NUM_FRAMES) + " Frames");
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

	return 0;
}
