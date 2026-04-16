#ifndef MOD_VERTEX_HPP
#define MOD_VERTEX_HPP

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/hash.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct vertex {
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 tex;

	bool operator==(const vertex& other) const {
		return  pos == other.pos &&
			col == other.col &&
			tex == other.tex;
	}
};

namespace std {
	template<> struct hash<vertex> {
		size_t operator()(vertex const& vert) const {
			return ((hash<glm::vec3>()(vert.pos) ^
			(hash<glm::vec3>()(vert.col) << 1)) >> 1) ^
			(hash<glm::vec2>()(vert.tex) << 1);
        }
    };
}

VkVertexInputBindingDescription vertex_get_bind_desc();

std::array<VkVertexInputAttributeDescription, 3> vertex_get_attrib_desc();

#endif
