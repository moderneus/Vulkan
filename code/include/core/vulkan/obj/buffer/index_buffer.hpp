#ifndef MOD_INDEX_BUFFER_HPP
#define MOD_INDEX_BUFFER_HPP

#include "core/vulkan/obj/buffer/buffer.hpp"

#include <cstdint>
#include <vector>

struct device;
struct physical_device;
struct command_pool;
struct queue;

struct index_buffer {
	buffer				ibuf;
	std::vector<uint32_t>		data;
};

void index_buffer_create(index_buffer *buf, const device &dev, const physical_device &gpu, const queue &q, const command_pool &pool);

void index_buffer_destroy(const index_buffer &buf, const device &dev);

#endif
