#include "core/vulkan/obj/buffer/shader_storage_buffer.hpp"
#include "util/constants.hpp"

#include <random>
#include <ctime>

void shader_storage_buffer_create(std::vector<shader_storage_buffer> *bufs, const device &dev, const physical_device &gpu, const queue &q, const command_pool &pool)
{
	std::default_random_engine rnd_engine((unsigned)time(nullptr));
	std::uniform_real_distribution<float> rnd_dist(0.0f, 1.0f);

	std::vector<vertex> particles(PARTICLE_COUNT);

	for(auto &particle : particles) {
		float r = 0.25f * sqrt(rnd_dist(rnd_engine));
		float theta = rnd_dist(rnd_engine) * 2.0f * 3.14159265358979323846f;
		float x = r * cos(theta) * 640 / 480;
		float y = r * sin(theta);
		particle.pos = glm::vec2(x, y);
		particle.vel = glm::normalize(glm::vec2(x, y)) * 0.00025f;
		particle.col = glm::vec4(rnd_dist(rnd_engine), rnd_dist(rnd_engine), rnd_dist(rnd_engine), 1.0f);
	}

	VkDeviceSize size = sizeof(vertex) * PARTICLE_COUNT;

	buffer staging_buf;

	buffer_create(&staging_buf, dev, gpu, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

	buffer_memcpy(&staging_buf, dev, particles, size);

	bufs->resize(MAX_FRAMES_IN_FLIGHT);

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		buffer_create(&bufs->data()[i].sbuf, dev, gpu, size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		buffer_copy(staging_buf, bufs->data()[i].sbuf, dev, q, pool, size);
	}

	buffer_destroy(staging_buf, dev);
}

void shader_storage_buffer_destroy(const std::vector<shader_storage_buffer> &bufs, const device &dev)
{
	for(uint32_t i = 0; i < bufs.size(); ++i)
		buffer_destroy(bufs[i].sbuf, dev);
}
