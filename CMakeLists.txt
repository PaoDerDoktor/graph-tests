cmake_minimum_required(VERSION 2.9)

project(Graph-Test)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(include)

add_executable(gradient src/gradient.cpp)
target_compile_definitions(gradient PRIVATE TARGET_GRADIENT)
target_link_libraries(gradient ${CONAN_LIBS})

add_executable(randomPattern src/randomPattern.cpp)
target_compile_definitions(randomPattern PRIVATE TARGET_RANDOMPATTERN)
target_link_libraries(randomPattern ${CONAN_LIBS})

add_executable(perlinNoise src/perlinNoise.cpp src/utils/Vect2D.cpp)
target_compile_definitions(perlinNoise PRIVATE TARGET_PERLINNOISE)
target_link_libraries(perlinNoise ${CONAN_LIBS})