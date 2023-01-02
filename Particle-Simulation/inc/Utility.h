#pragma once
#include <cstdio>	
#include <cstdint> 
#include <string>
#include <chrono>   //For Timing

#include "Config.h"

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

//Timing Functor
class Timer {
public:
	explicit Timer(std::string name = "UNNAMED") {
		profile = name;
		start = std::chrono::high_resolution_clock::now();
		printf("\nStarting Timing for [%s]", name.c_str());
	}
	~Timer() {
		end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		double durSeconds = duration.count() / 1000000.0;
		printf("\n[%s] finished in %f Seconds\n\tAverage: <%f>\n\tTarget: <%f>", profile.c_str(), durSeconds, durSeconds / NUM_FRAMES, (durSeconds / NUM_FRAMES) - TARGET_FRAMERATE);
	}

private:
	std::string profile;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
};


