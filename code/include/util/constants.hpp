#ifndef MOD_CONSTANTS_HPP
#define MOD_CONSTANTS_HPP

#include <cstdint>
#include <array>
#include <string>

inline constexpr const uint32_t PARTICLE_COUNT = 8192;

inline constexpr const uint32_t MAX_FRAMES_IN_FLIGHT = 2;

inline const std::array<std::string, 3> shdr_paths = {
	"shaders/vert/particle.vert.spv",
	"shaders/frag/particle.frag.spv",
	"shaders/comp/particle.comp.spv"
};

#endif
