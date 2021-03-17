cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Stb)

add_library(stb STATIC include/stb/stb_image.h src/stb_image.cpp)
target_include_directories(stb PUBLIC include/)