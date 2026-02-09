#include "core/vulkan/objects/instance/Instance.hpp"
#include "core/vulkan/objects/debug/DebugMessenger.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"
#include "util/String.hpp"

#include "SDL3/SDL_vulkan.h"

#include <vulkan/vulkan.h>

#include <cstdint>

std::vector<const char*> instance_get_req_exts() 
{
	uint32_t exts_count = 0;
	const char* const* exts = SDL_Vulkan_GetInstanceExtensions(&exts_count);

	std::vector<const char*> exts_vec(exts, exts + exts_count);
	exts_vec.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	log_info("Extensions = ", cstr_vec_to_str_vec(exts_vec));
	log_info("Extensions count = " + std::to_string(exts_vec.size()));

	return exts_vec;
}

VkApplicationInfo instance_create_app_info() 
{
	log_info("Creating an Application Info...");

	VkApplicationInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.applicationVersion = VK_MAKE_VERSION(1, 1, 0);
	info.engineVersion = VK_MAKE_VERSION(0, 1, 2);
	info.apiVersion = VK_API_VERSION_1_4;

	log_info("The Application Info created.");

	return info;
}

VkInstanceCreateInfo instance_create_info
(
	const VkApplicationInfo					*app_info, 
	const VkDebugUtilsMessengerCreateInfoEXT		*msgr_info, 
	const std::vector<const char*>				&exts
) 
{
	log_info("Creating the Instance Info...");

	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pNext = nullptr;
	info.pApplicationInfo = app_info;
	info.enabledExtensionCount = static_cast<uint32_t>(exts.size());
	info.ppEnabledExtensionNames = reinterpret_cast<const char* const*>(exts.data());

	log_info("Checking a Valiation Layers Support...");

	if (check_validation_layers_support()) {
		log_info("The Validation layers is supported.");
		info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		info.ppEnabledLayerNames = validationLayers.data();
		info.pNext = msgr_info;
	} else {
		log_error("The Validation Layers doesn't supported.");
		info.enabledLayerCount = 0;
		info.ppEnabledLayerNames = nullptr;
	}

	log_info("The Instance info was created.");

	return info;
}

void instance_create(instance_t *instance) 
{
	log_info("Creating an Instance...");

	VkApplicationInfo app_info = instance_create_app_info();
	VkDebugUtilsMessengerCreateInfoEXT msgr_info = dbg_msgr_create_info();
	std::vector<const char*> exts = instance_get_req_exts();
	VkInstanceCreateInfo instance_info = instance_create_info(&app_info, &msgr_info, exts);

	if (vkCreateInstance(&instance_info, nullptr, &instance->handle) != VK_SUCCESS) {
		log_critical("Failed to Create Instance.");
	}

	log_info("The Instance was Created.");
}

void instance_destroy(const instance_t &instance) 
{
	log_info("Destroying the Instance...");

	if (instance.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Instance::Instance is not Created.");
	}

	vkDestroyInstance(instance.handle, nullptr);

	log_info("The Instance was Destroyed.");
}
