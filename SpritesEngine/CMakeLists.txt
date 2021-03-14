# CMakeList.txt : CMake project for SpritesEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (SpritesEngine "SpritesEngine.cpp" )

# TODO: Add tests and install targets if needed.
target_link_libraries(SpritesEngine
glfw
libglew_static
)