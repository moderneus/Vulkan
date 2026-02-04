#ifndef MOD_QUEUE_FAMILY_HPP
#define MOD_QUEUE_FAMILY_HPP

#include <vulkan/vulkan.h>

#include <cstdint>
#include <optional>

struct phys_device_t;
struct surface_t;

struct queue_family_t
{
	std::optional<uint32_t>		graphics;
	std::optional<uint32_t>		present;
};

bool queue_family_is_complete();

void queue_family_find(queue_family_t* queue_family, const phys_device_t& phys_device, const surface_t& surface);

#endif
