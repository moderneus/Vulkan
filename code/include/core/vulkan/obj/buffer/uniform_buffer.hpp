#ifndef MOD_UNIFORM_HPP
#define MOD_UNIFORM_HPP

#include "core/vulkan/obj/buffer/buffer.hpp"

#include "glm/glm.hpp"

struct swapchain_state;

struct uniform_buffer {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	buffer ubuf;
};

void uniform_buffer_create(std::vector<uniform_buffer> *bufs, const device &dev, const physical_device &gpu);

void uniform_buffer_destroy(const std::vector<uniform_buffer> &bufs, const device &dev);

void uniform_buffer_update(std::vector<uniform_buffer> *bufs, const swapchain_state &st, uint32_t frame);

#endif
