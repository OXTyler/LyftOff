cmake_minimum_required(VERSION 3.19)
project(TylersCode)

set(CMAKE_CUDA_STANDARD 14)

add_executable(TylersCode main.cpp Graph.h Graph.cpp)
