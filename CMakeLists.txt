cmake_minimum_required(VERSION 3.24)
project(MobiusCode)

set(CMAKE_CXX_STANDARD 20)

add_executable(MobiusCode src/main.cpp src/colour.cpp src/colour.hpp shared/definitions.hpp src/endian.hpp shared/vec2.hpp src/program.cpp src/program.hpp src/tape.cpp src/tape.hpp)
target_include_directories(MobiusCode PUBLIC shared)

add_executable(MobiusCodeHelper helper/main.cpp)
target_include_directories(MobiusCodeHelper PUBLIC shared)