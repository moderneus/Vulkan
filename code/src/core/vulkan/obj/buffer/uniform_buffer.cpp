#include "core/vulkan/obj/buffer/uniform_buffer.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/constants.hpp"
#include "util/debug/log.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include "glm/gtc/matrix_transform.hpp"

#include <cstring>
#include <chrono>

void uniform_buffer_create(std::vector<uniform_buffer> *bufs, const device &dev, const physical_device &gpu)
{
	log_info("Creating the Uniform Buffers...");

	VkDeviceSize size = sizeof(uniform_buffer) - sizeof(buffer);

	bufs->resize(MAX_FRAMES_IN_FLIGHT);

	for(uint32_t i = 0; i < bufs->size(); ++i) {
		buffer_create(&bufs->data()[i].ubuf, dev, gpu, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		vkMapMemory(dev.handle, bufs->data()[i].ubuf.mem, 0, size, 0, &bufs->data()[i].ubuf.data);
	}

	log_info("The Uniform Buffers were Created.");
}

void uniform_buffer_destroy(const std::vector<uniform_buffer> &bufs, const device &dev)
{
	log_info("Destroying the Uniform Buffers...");

	for(uint32_t i = 0; i < bufs.size(); ++i)
		buffer_destroy(bufs[i].ubuf, dev);

	log_info("The Uniform Buffers were Destroyed.");
}

void uniform_buffer_update(std::vector<uniform_buffer> *bufs, const swapchain_state &st, uint32_t frame)
{
	static auto start = std::chrono::high_resolution_clock::now();

	auto now = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(now - start).count();

	uniform_buffer ubo = {};
	ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ubo.proj = glm::perspective(glm::radians(45.0f), st.imgs[0].extent.width / static_cast<float>(st.imgs[0].extent.height), 0.1f, 10.0f);
	ubo.proj[1][1] *= -1;

	memcpy(bufs->data()[frame].ubuf.data, &ubo, sizeof(ubo));
}
