#ifndef MOD_INSTANCE_HPP
#define MOD_INSTANCE_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct instance {
	VkInstance handle = VK_NULL_HANDLE;
};

VkApplicationInfo instance_create_app_info();

VkInstanceCreateInfo instance_create_info(const VkApplicationInfo &app_info, const VkDebugUtilsMessengerCreateInfoEXT &msgr_info, const std::vector<const char*> &exts);

std::vector<const char*> instance_get_req_exts();

void instance_create(instance *inst);

void instance_destroy(const instance &inst);

#endif
