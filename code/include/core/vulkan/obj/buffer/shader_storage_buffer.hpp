#ifndef MOD_SHADER_STORAGE_BUFFER_HPP
#define MOD_SHADER_STORAGE_BUFFER_HPP

#include "core/vulkan/obj/buffer/buffer.hpp"

struct physical_device;
struct device;

struct shader_storage_buffer {
	buffer sbuf;
};

void shader_storage_buffer_create(std::vector<shader_storage_buffer> *bufs, const device &dev, const physical_device &gpu, const queue &q, const command_pool &pool);

void shader_storage_buffer_destroy(const std::vector<shader_storage_buffer> &bufs, const device &dev);

#endif
