# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("SpritesEngine")

# Include sub-projects.
add_subdirectory (glfw)
add_subdirectory (glew)
add_subdirectory ("SpritesEngine")

target_include_directories (SpritesEngine PUBLIC ${CMAKE_INCLUDE_CURRENT_DIR}glfw/include)
target_include_directories (SpritesEngine PUBLIC ${CMAKE_INCLUDE_CURRENT_DIR}glew/include)