cmake_minimum_required(VERSION 4.1.0)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET Vulkan)

project(${TARGET} LANGUAGES CXX)

add_subdirectory("libs/fmt")
add_subdirectory("libs/SDL")
add_subdirectory("libs/glm")

find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(${TARGET} ${SRC})

target_compile_options(${TARGET} PRIVATE -std=c++20 -g -O1 -Wall -Wextra -Wpedantic -frtti -fexceptions)
target_include_directories(${TARGET} PRIVATE include libs/SDL/include libs/fmt/include libs/glm libs/stb)
target_link_libraries(${TARGET} PRIVATE SDL3::SDL3 fmt::fmt Vulkan::Vulkan)

set(DYNAMIC_LIBS SDL3::SDL3 fmt::fmt glm::glm)

foreach(lib IN LISTS DYNAMIC_LIBS)
        add_custom_command(
		TARGET ${TARGET} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:${lib}>
		$<TARGET_FILE_DIR:${TARGET}>
        )
endforeach()

file(COPY assets DESTINATION .)

find_program(GLSLC glslc REQUIRED)

set(SHADERS_SRC_DIR ${CMAKE_SOURCE_DIR}/shaders)
set(SHADERS_BIN_DIR ${CMAKE_BINARY_DIR}/shaders)

file(GLOB_RECURSE SHADER_SOURCES
    ${SHADERS_SRC_DIR}/*.vert
    ${SHADERS_SRC_DIR}/*.frag
)

set(SHADER_BINARIES "")

foreach(SHADER ${SHADER_SOURCES})
    file(RELATIVE_PATH REL_PATH ${SHADERS_SRC_DIR} ${SHADER})

    set(OUTPUT ${SHADERS_BIN_DIR}/${REL_PATH}.spv)

    get_filename_component(OUTPUT_DIR ${OUTPUT} DIRECTORY)
    file(MAKE_DIRECTORY ${OUTPUT_DIR})

    add_custom_command(
        OUTPUT ${OUTPUT}
        COMMAND ${GLSLC} ${SHADER} -o ${OUTPUT}
        DEPENDS ${SHADER}
        COMMENT "Compiling shader ${REL_PATH}"
    )

    list(APPEND SHADER_BINARIES ${OUTPUT})
endforeach()

add_custom_target(shaders ALL
    DEPENDS ${SHADER_BINARIES}
)

add_dependencies(${TARGET} shaders)
