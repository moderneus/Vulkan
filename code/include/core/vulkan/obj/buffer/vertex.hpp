#ifndef MOD_VERTEX_HPP
#define MOD_VERTEX_HPP

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct vertex {
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 tex;
};

const std::vector<vertex> rectangles_verts = {
	{{-0.5f, -0.5f,  0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
	{{ 0.5f, -0.5f,  0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
	{{ 0.5f,  0.5f,  0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
	{{-0.5f,  0.5f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

	{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
	{{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
	{{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
	{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
};

const std::vector<uint32_t> rectangles_indices = {
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 6, 7, 4
};

VkVertexInputBindingDescription vertex_get_bind_desc();

std::array<VkVertexInputAttributeDescription, 3> vertex_get_attrib_desc();

#endif
