#include "core/vulkan/obj/image/texture.hpp"
#include "core/vulkan/obj/image/image.hpp"
#include "core/vulkan/obj/buffer/buffer.hpp"
#include "util/debug/log.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

void texture_create(texture *tex, const device &dev, const physical_device &gpu, const queue &q, const command_pool &pool, const std::string &path)
{
	tex->img.data = stbi_load(path.c_str(), reinterpret_cast<int*>(&tex->img.extent.width), reinterpret_cast<int*>(&tex->img.extent.height), reinterpret_cast<int*>(&tex->img.channels), STBI_rgb_alpha);

	if (!tex->img.data)
		log_error("Failed to Load Texture by path: ", path);

	VkDeviceSize size = tex->img.extent.width * tex->img.extent.height * 4;

	buffer staging_buf;

	buffer_create(&staging_buf, dev, gpu, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	buffer_memcpy(&staging_buf, dev, tex->img, size);

	stbi_image_free(tex->img.data);

	tex->img.fmt = VK_FORMAT_R8G8B8A8_SRGB;
	tex->img.tiling = VK_IMAGE_TILING_OPTIMAL;
	tex->img.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	image_create(&tex->img, dev, gpu, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	image_transition_layout(tex->img, dev, q, pool, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

		buffer_copy_to_image(staging_buf, tex->img, dev, pool, q);

	image_transition_layout(tex->img, dev, q, pool, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	buffer_destroy(staging_buf, dev);
}

void texture_destroy(const texture &tex, const device &dev)
{
	image_destroy(tex.img, dev);
}
