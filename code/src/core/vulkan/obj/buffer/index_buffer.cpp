#include "core/vulkan/obj/buffer/index_buffer.hpp"

void index_buffer_create(index_buffer *buf, const device &dev, const physical_device &gpu, const queue &q, const command_pool &pool)
{
	VkDeviceSize size = sizeof(buf->data[0]) * buf->data.size();

	buffer staging_buf = {};
	buffer_create(&staging_buf, dev, gpu, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	buffer_memcpy(&staging_buf, dev, buf->data, size);

	buffer_create(&buf->ibuf, dev, gpu, size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	buffer_copy(staging_buf, buf->ibuf, dev, q, pool, size);

	buffer_destroy(staging_buf, dev);
}

void index_buffer_destroy(const index_buffer &buf, const device &dev)
{
	buffer_destroy(buf.ibuf, dev);
}
