#ifndef MOD_TEXTURE_HPP
#define MOD_TEXTURE_HPP

#include "core/vulkan/obj/buffer/buffer.hpp"
#include "core/vulkan/obj/image/image.hpp"

#include <string>

struct physical_device;
struct device;

struct texture {
	image img;
	buffer tbuf;
};

void texture_create(texture *tex, const device &dev, const physical_device &gpu, const queue &q, const command_pool &pool, const std::string &path);

void texture_destroy(const texture &tex, const device &dev);

#endif
