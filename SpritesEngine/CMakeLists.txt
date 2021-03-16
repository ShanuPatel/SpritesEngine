
# CMakeList.txt : CMake project for SpritesEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.3)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/vert.glsl
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/shaders/frag.glsl
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
# Add source to this project's executable.
add_executable (SpritesEngine "SpritesEngine.cpp" )

# TODO: Add tests and install targets if needed.
target_link_libraries(SpritesEngine
glad
glfw
libglew_static
)