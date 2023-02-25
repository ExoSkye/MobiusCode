cmake_minimum_required(VERSION 3.24)
project(MobiusCode)

set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -mtune=znver3)
    add_link_options(-flto=full)
endif()

if (ASAN)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

add_executable(MobiusCode src/main.cpp src/colour.cpp src/colour.hpp shared/definitions.hpp src/endian.hpp shared/vec2.hpp src/program.cpp src/program.hpp src/tape.cpp src/tape.hpp)
target_include_directories(MobiusCode PUBLIC shared)

add_executable(MobiusCodeHelper helper/main.cpp)
target_include_directories(MobiusCodeHelper PUBLIC shared)
