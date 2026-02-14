#ifndef MOD_INSTANCE_HPP
#define MOD_INSTANCE_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct instance_t
{
	VkInstance handle = VK_NULL_HANDLE;
};

VkApplicationInfo inst_create_app_info();

VkInstanceCreateInfo inst_create_info
(
	const VkApplicationInfo					*app_info, 
	const VkDebugUtilsMessengerCreateInfoEXT		*dbg_info, 
	const std::vector<const char*>				&exts
);

std::vector<const char*> inst_get_req_exts();

void inst_create(instance_t *inst);

void inst_destroy(const instance_t &inst);

#endif
