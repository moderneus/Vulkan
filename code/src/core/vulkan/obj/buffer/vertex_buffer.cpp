#include "core/vulkan/obj/buffer/vertex_buffer.hpp"

void vertex_buffer_create(vertex_buffer *buf, const device &dev, const physical_device &gpu, const queue &q, const command_pool &pool)
{
	VkDeviceSize size = sizeof(buf->data[0]) * buf->data.size();

	buffer staging_buf = {};
	buffer_create(&staging_buf, dev, gpu, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	buffer_memcpy(&staging_buf, dev, buf->data, size);

	buffer_create(&buf->vbuf, dev, gpu, size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	buffer_copy(staging_buf, buf->vbuf, dev, q, pool, size);

	buffer_destroy(staging_buf, dev);
}

void vertex_buffer_destroy(const vertex_buffer &buf, const device &dev)
{
	buffer_destroy(buf.vbuf, dev);
}
