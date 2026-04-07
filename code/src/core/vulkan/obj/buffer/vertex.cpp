#include "core/vulkan/obj/buffer/vertex.hpp"

VkVertexInputBindingDescription vertex_get_bind_desc()
{
	VkVertexInputBindingDescription desc = {};
	desc.binding = 0;
	desc.stride = sizeof(vertex);
	desc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	return desc;
}

std::array<VkVertexInputAttributeDescription, 3> vertex_get_attrib_desc()
{
	std::array<VkVertexInputAttributeDescription, 3> descs = {};

	descs[0].binding = 0;
	descs[0].location = 0;
	descs[0].format = VK_FORMAT_R32G32_SFLOAT;
	descs[0].offset = offsetof(vertex, pos);

	descs[1].binding = 0;
	descs[1].location = 1;
	descs[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	descs[1].offset = offsetof(vertex, col);

	descs[2].binding = 0;
	descs[2].location = 2;
	descs[2].format = VK_FORMAT_R32G32_SFLOAT;
	descs[2].offset = offsetof(vertex, tex);

	return descs;
}
