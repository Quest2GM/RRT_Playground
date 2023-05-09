cmake_minimum_required(VERSION 3.10)
project(RRTPlayground LANGUAGES CXX)
add_executable(RRT RRT.cpp)
target_compile_features(RRT PRIVATE cxx_std_20)