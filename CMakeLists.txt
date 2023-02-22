cmake_minimum_required(VERSION 3.24)
project(MobiusCode)

set(CMAKE_CXX_STANDARD 20)

add_executable(MobiusCode main.cpp colour.cpp colour.hpp definitions.hpp endian.hpp vec2.hpp program.cpp program.hpp tape.cpp tape.hpp)
