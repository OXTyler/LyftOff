cmake_minimum_required(VERSION 3.19)
project(TylersCode)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(TylersCode main.cpp Graph.h Graph.cpp)

target_link_libraries(TylersCode -lopengl32  -lfreeglut -lglut)

