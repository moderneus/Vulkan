#include "core/vulkan/obj/image/texture.hpp"
#include "core/vulkan/obj/image/image.hpp"
#include "util/debug/log.hpp"

#include "stb_image.h"

#include <string>

void texture_create(texture *tex, const device &dev, const physical_device &gpu, const std::string &path)
{
	stbi_uc *pixels = stbi_load(path.c_str(), &tex->img.width, &tex->img.height, &tex->img.channels, STBI_rgb_alpha);

	if (!pixels)
		log_error("Failed to Load Texture by path: ", path);

	VkDeviceSize size = tex->img.width * tex->img.height * sizeof(uint32_t);

	buffer staging_buf;

	buffer_create(&staging_buf, dev, gpu, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	buffer_memcpy(&staging_buf, dev, tex->img, size);

	stbi_image_free(pixels);

	tex->img.fmt = VK_FORMAT_R8G8B8A8_SRGB;
	tex->img.tiling = VK_IMAGE_TILING_OPTIMAL;
	tex->img.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED;
	image_create(&tex->img, dev, gpu, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
}

void texture_destroy(const texture &tex, const device &dev)
{
	image_destroy(tex.img, dev);
}
