# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.3)

project ("SpritesEngine")

# Include sub-projects.
add_subdirectory (Libraries/glad)
add_subdirectory (Libraries/glfw)
add_subdirectory (Libraries/glew)
add_subdirectory (Libraries/stb)
add_subdirectory ("SpritesEngine")

target_include_directories (SpritesEngine PUBLIC ${CMAKE_INCLUDE_CURRENT_DIR}/Libraries/glfw/include)
target_include_directories (SpritesEngine PUBLIC ${CMAKE_INCLUDE_CURRENT_DIR}/Libraries/glew/include)
