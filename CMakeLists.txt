cmake_minimum_required(VERSION 3.10)

project(EcosystemModel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES 
    src/main.cpp 
    src/Grid.cpp 
    src/Simulation.cpp 
    src/Visualizer.cpp 
    src/DataLogger.cpp
)

add_executable(ecosys ${SOURCES})

target_compile_options(ecosys PRIVATE -Wall)

target_include_directories(ecosys PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)