#ifndef MOD_VERTEX_BUFFER_HPP
#define MOD_VERTEX_BUFFER_HPP

#include "core/vulkan/obj/buffer/buffer.hpp"
#include "core/vulkan/obj/buffer/vertex.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>
#include <vector>

struct device;
struct physical_device;
struct command_pool;
struct queue;

struct vertex_buffer {
	buffer				vbuf;
	std::vector<vertex>		data;
};

void vertex_buffer_create(vertex_buffer *buf, const device &dev, const physical_device &gpu, const queue &q, const command_pool &pool);

void vertex_buffer_destroy(const vertex_buffer &buf, const device &dev);

#endif
