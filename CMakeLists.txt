cmake_minimum_required(VERSION 4.1.0)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

set(TARGET Vulkan)

project(${TARGET} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt REQUIRED)
find_package(SDL3 REQUIRED)
find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(${TARGET} ${SRC})

target_include_directories(${TARGET} PRIVATE headers)
target_link_libraries(${TARGET} PRIVATE fmt::fmt SDL3::SDL3 Vulkan::Vulkan)