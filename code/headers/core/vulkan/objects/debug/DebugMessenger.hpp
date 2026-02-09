#ifndef MOD_DEBUG_MSGR_HPP
#define MOD_DEBUG_MSGR_HPP

#include <vulkan/vulkan.h>

struct instance_t;

struct debug_msgr_t 
{
	VkDebugUtilsMessengerEXT handle = VK_NULL_HANDLE;
};

VKAPI_ATTR VkBool32 VKAPI_CALL callback
(
	VkDebugUtilsMessageSeverityFlagBitsEXT				msg_sev,
	VkDebugUtilsMessageTypeFlagsEXT					msg_type,
	const VkDebugUtilsMessengerCallbackDataEXT		       *cb_data,
	void							       *usr_data 
);

VkDebugUtilsMessengerCreateInfoEXT dbg_msgr_create_info();

VkResult dbg_msgr_create
(
	debug_msgr_t						       *msgr,
	const instance_t					       &instance,
	const VkDebugUtilsMessengerCreateInfoEXT		       *info,
	const VkAllocationCallbacks				       *alloc
);

VkResult dbg_msgr_destroy(debug_msgr_t *msgr, const instance_t &instance);

void dbg_msgr_setup(debug_msgr_t *msgr, const instance_t &instance);

#endif
