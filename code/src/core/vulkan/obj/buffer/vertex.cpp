#include "core/vulkan/objects/buffers/types/Vertex.hpp"

VkVertexInputBindingDescription vertex_get_bind_desc()
{
	VkVertexInputBindingDescription desc = {};
	desc.binding = 0;
	desc.stride = sizeof(vertex);
	desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return desc;
}

std::array<VkVertexInputAttributeDescription, 2> vertex_get_attrib_desc()
{
	std::array<VkVertexInputAttributeDescription, 2> descs = {};
	descs[0].binding = 0;
	descs[0].location = 0;
	descs[0].format = VK_FORMAT_R32G32_SFLOAT;
	descs[0].offset = offsetof(vertex, pos);

	descs[1].binding = 0;
	descs[1].location = 1;
	descs[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	descs[1].offset = offsetof(vertex, col);
	return descs;
}
