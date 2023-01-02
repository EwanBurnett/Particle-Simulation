project(Particle-Simulation)

message(STATUS "Particle Simulation\nAuthor - Ewan Burnett\nStart Date - 02/01/2023\n\nA Particle Project intended to practice concurrency and parallelism mechanisms with C++.")
add_executable(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
