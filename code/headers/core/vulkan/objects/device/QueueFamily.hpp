#ifndef MOD_QF_HPP
#define MOD_QF_HPP

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

bool qf_is_complete();

void qf_find(queue_family_t *qf, const phys_device_t &phys_dev, const surface_t &surface);

#endif
