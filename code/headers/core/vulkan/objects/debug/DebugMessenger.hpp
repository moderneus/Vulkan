#ifndef MOD_DEBUG_MESSENGER_HPP
#define MOD_DEBUG_MESSENGER_HPP

#include <vulkan/vulkan.h>

struct instance_t;

struct debug_msgr_t
{
		VkDebugUtilsMessengerEXT handle = VK_NULL_HANDLE;
};

VKAPI_ATTR VkBool32 VKAPI_CALL callback
(
		VkDebugUtilsMessageSeverityFlagBitsEXT						msg_severity,
		VkDebugUtilsMessageTypeFlagsEXT								msg_type,
		const VkDebugUtilsMessengerCallbackDataEXT*					pcallback_data,
		void*														puser_data 
);

VkDebugUtilsMessengerCreateInfoEXT debug_msgr_create_info();

VkResult debug_msgr_create 
(
		debug_msgr_t*											debug_msgr,
		const instance_t&										instance,
		const VkDebugUtilsMessengerCreateInfoEXT*				pcreate_info,
		const VkAllocationCallbacks*							pallocator
);

VkResult debug_msgr_destroy(debug_msgr_t* debug_msgr, const instance_t& instance);

void debug_msgr_setup(debug_msgr_t* debug_mgsr, const instance_t& instance);

#endif
