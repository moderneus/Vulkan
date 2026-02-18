#ifndef MOD_MESSENGER_HPP
#define MOD_MESSENGER_HPP

#include <vulkan/vulkan.h>

struct instance;

struct messenger {
	VkDebugUtilsMessengerEXT handle = VK_NULL_HANDLE;
};

VKAPI_ATTR VkBool32 VKAPI_CALL callback(VkDebugUtilsMessageSeverityFlagBitsEXT sev, VkDebugUtilsMessageTypeFlagsEXT type, 
					const VkDebugUtilsMessengerCallbackDataEXT *cb_data, void *usr_data);

VkDebugUtilsMessengerCreateInfoEXT messenger_create_info();

VkResult messenger_create(messenger *msgr, const instance &inst, const VkDebugUtilsMessengerCreateInfoEXT &info, 
			  const VkAllocationCallbacks *alloc);

void messenger_setup(messenger *msgr, const instance &inst);

VkResult messenger_destroy(const messenger &msgr, const instance &inst);

#endif
