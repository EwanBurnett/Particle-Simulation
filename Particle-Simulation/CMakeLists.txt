project(Particle-Simulation)


message(STATUS "Particle Simulation\nAuthor - Ewan Burnett\nStart Date - 02/01/2023\n\nA Particle Project intended to practice concurrency and parallelism mechanisms with C++.")
add_executable(${PROJECT_NAME} "src/main.cpp" "inc/Particle.h" "inc/Utility.h" "inc/Config.h")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
