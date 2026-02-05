#include "core/vulkan/objects/buffers/types/Vertex.hpp"

VkVertexInputBindingDescription vertex_get_binding_description()
{
	VkVertexInputBindingDescription description = {};
	description.binding = 0;
	description.stride = sizeof(vertex_t);
	description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return description;
}

std::array<VkVertexInputAttributeDescription, 2> vertex_get_attrib_description()
{
	std::array<VkVertexInputAttributeDescription, 2> attrrib_descriptions = {};
	attrrib_descriptions[0].binding = 0;
	attrrib_descriptions[0].location = 0;
	attrrib_descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attrrib_descriptions[0].offset = offsetof(vertex_t, pos);

	attrrib_descriptions[1].binding = 0;
	attrrib_descriptions[1].location = 1;
	attrrib_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attrrib_descriptions[1].offset = offsetof(vertex_t, col);
	return attrrib_descriptions;
}
