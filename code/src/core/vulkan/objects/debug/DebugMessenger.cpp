#include "core/vulkan/objects/debug/DebugMessenger.hpp"
#include "core/vulkan/objects/instance/Instance.hpp"
#include "util/debug/Logger.hpp"

#include "fmt/core.h"
#include "fmt/color.h"

#include <vulkan/vulkan.h>

VKAPI_ATTR VkBool32 VKAPI_CALL callback
(
	VkDebugUtilsMessageSeverityFlagBitsEXT				 msg_sev,
	VkDebugUtilsMessageTypeFlagsEXT					 msg_type,
	const VkDebugUtilsMessengerCallbackDataEXT			*cb_data,
	void								*user_data
)
{
	fmt::color col;

	switch(msg_sev) {
	default:
		col = fmt::color::white;
	break;

	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		col = fmt::color::gray;
	break;

	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		col = fmt::color::gold;
	break;

	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		col = fmt::color::red;
	break;

	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		col = fmt::color::blue;
	break;
	}

	fmt::print(fmt::fg(fmt::color::dark_red), "[VULKAN] ");
	fmt::print(fmt::fg(col), "{}: ", cb_data->pMessageIdName);
	fmt::print(fmt::fg(fmt::color::white), "{}\n", cb_data->pMessage);

	return VK_FALSE;
}

VkDebugUtilsMessengerCreateInfoEXT dbg_msgr_create_info() 
{
	log_info("Creating a Debug Messenger Info...");

	VkDebugUtilsMessengerCreateInfoEXT info = {};
	info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

	info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
			       VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			       VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
			       VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;

	info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
			   VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	info.pfnUserCallback = callback;
	info.pUserData = nullptr;

	log_info("The Debug Messenger Info was created.");

	return info;
}

VkResult dbg_msgr_create
(
	debug_msgr_t							*msgr,
	const instance_t						&instance,
	const VkDebugUtilsMessengerCreateInfoEXT			*info, 
	const VkAllocationCallbacks					*alloc
) 
{    
	log_info("Creating a Debug Messenger...");

	auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance.handle, "vkCreateDebugUtilsMessengerEXT");

	if (func != nullptr) {
		func(instance.handle, info, alloc, &msgr->handle);
	} else {
		log_error("Failed to Create the Debug Messegner::Extension not Present!");
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	log_info("The Debug Messenger was Created.");

	return VK_SUCCESS;
}

VkResult dbg_msgr_destroy(const debug_msgr_t &msgr, const instance_t &instance) 
{
	log_info("Destroying the Debug Messenger...");

	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance.handle, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance.handle, msgr.handle, nullptr);
	} else {
		log_error("Failed to Destroy the Debug Messenger::Extension not Present!");
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}

	log_info("The Debug Messenger was Destroyed.");

	return VK_SUCCESS;
}

void dbg_msgr_setup(debug_msgr_t *msgr, const instance_t &instance) 
{
	log_info("Setting up a Debug Messenger...");

	VkDebugUtilsMessengerCreateInfoEXT msgr_info = dbg_msgr_create_info();
	if (dbg_msgr_create(msgr, instance, &msgr_info, nullptr) != VK_SUCCESS) {
		log_error("Failed to Create the Debug Messenger.");
	}

	log_info("The Debug Messenger was Setted up.");
}
