#ifndef MOD_CONSTANTS_HPP
#define MOD_CONSTANTS_HPP

#include <cstdint>
#include <array>
#include <string>

inline constexpr const uint32_t MAX_FRAMES_IN_FLIGHT = 2;

inline const std::array<std::string, 2> shdr_paths = {
	"shaders/vert/square.vert.spv",
	"shaders/frag/square.frag.spv"
};

#endif
