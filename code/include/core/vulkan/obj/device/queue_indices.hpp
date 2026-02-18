#ifndef MOD_QUEUE_INDICES_HPP
#define MOD_QUEUE_INDICES_HPP

#include <vulkan/vulkan.h>

#include <cstdint>
#include <optional>

struct physical_device;
struct surface;

struct queue_indices {
	std::optional<uint32_t>	gfx;
	std::optional<uint32_t> pres;
};

bool queue_indices_is_complete(const queue_indices &q_idx);

void queue_indices_find(queue_indices *q_idx, const physical_device &gpu, const surface &surf);

#endif
