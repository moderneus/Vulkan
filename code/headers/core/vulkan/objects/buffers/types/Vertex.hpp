#ifndef MOD_VERTEX_HPP
#define MOD_VERTEX_HPP

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct vertex_t
{
	glm::vec2 pos;
	glm::vec3 col;
};

const std::vector<vertex_t> vertices = 
{
    {{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
    {{0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

VkVertexInputBindingDescription vertex_get_binding_description();

std::array<VkVertexInputAttributeDescription, 2> vertex_get_attrib_description();

#endif
