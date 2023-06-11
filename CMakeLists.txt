cmake_minimum_required(VERSION 3.25)
project(hopper_problem_sim)

set(CMAKE_CXX_STANDARD 17)

add_executable(hopper_problem_sim src/main.cpp src/IterativeSimulation.cpp src/IterativeSimulation.h src/hp.cpp src/hp.h)
