cmake_minimum_required(VERSION 4.1.0)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET Vulkan)

project(${TARGET} LANGUAGES CXX)

set(FMT "libs/fmt")
set(SDL "libs/SDL")

add_subdirectory(${FMT})
add_subdirectory(${SDL})

find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(${TARGET} ${SRC})

target_compile_options(${TARGET} PRIVATE -g -std=c++20 -O2 -Wall -Wextra -Wpedantic -frtti -fexceptions)
target_include_directories(${TARGET} PRIVATE headers libs/SDL/include libs/fmt/include)
target_link_libraries(${TARGET} PRIVATE SDL3::SDL3 fmt::fmt Vulkan::Vulkan)

set(DYNAMIC_LIBS SDL3::SDL3 fmt::fmt)

foreach(lib IN LISTS DYNAMIC_LIBS)
    get_target_property(lib_type ${lib} TYPE)
    if(lib_type STREQUAL "SHARED_LIBRARY")
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${lib}>
                $<TARGET_FILE_DIR:${TARGET}>
        )
    endif()
endforeach()

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
