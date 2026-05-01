#include "core/vulkan/obj/instance/instance.hpp"
#include "core/vulkan/obj/debug/messenger.hpp"
#include "util/debug/val_layers.hpp"
#include "util/debug/log.hpp"
#include "util/string.hpp"

#include "SDL3/SDL_vulkan.h"

#include <vulkan/vulkan.h>

#include <cstdint>

std::vector<const char*> instance_get_req_exts() 
{
	log_info("Getting the Required Extensions...");

	uint32_t exts_cnt = 0;
	const char* const* exts = SDL_Vulkan_GetInstanceExtensions(&exts_cnt);

	std::vector<const char*> req_exts(exts, exts + exts_cnt);
	req_exts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	log_info("The Required Extensions were Got: ", cstr_vec_to_str_vec(req_exts));

	return req_exts;
}

VkApplicationInfo instance_create_app_info() 
{
	log_info("Creating an Application Info...");

	VkApplicationInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.applicationVersion = VK_MAKE_VERSION(1, 1, 1);
	info.engineVersion = VK_MAKE_VERSION(0, 1, 2);
	info.apiVersion = VK_API_VERSION_1_4;

	log_info("The Application Info created.");

	return info;
}

VkInstanceCreateInfo instance_create_info(const VkApplicationInfo &app_info, const VkDebugUtilsMessengerCreateInfoEXT &msgr_info, const std::vector<const char*> &exts) 
{
	log_info("Creating the Instance Info...");

	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pNext = nullptr;
	info.pApplicationInfo = &app_info;
	info.enabledExtensionCount = static_cast<uint32_t>(exts.size());
	info.ppEnabledExtensionNames = reinterpret_cast<const char* const*>(exts.data());

	log_info("Checking a Valiation Layers Support...");

	if (val_layers_check_supp()) {
		log_info("The Validation layers is supported.");
		info.enabledLayerCount = static_cast<uint32_t>(val_layers.size());
		info.ppEnabledLayerNames = val_layers.data();
		info.pNext = &msgr_info;
	} else {
		log_error("The Validation Layers doesn't supported.");
		info.enabledLayerCount = 0;
		info.ppEnabledLayerNames = nullptr;
	}

	log_info("The Instance info was created.");

	return info;
}

void instance_create(instance *inst) 
{
	log_info("Creating an Instance...");

	VkApplicationInfo app_info = instance_create_app_info();
	VkDebugUtilsMessengerCreateInfoEXT msgr_info = messenger_create_info();
	std::vector<const char*> exts = instance_get_req_exts();
	VkInstanceCreateInfo info = instance_create_info(app_info, msgr_info, exts);

	if (vkCreateInstance(&info, nullptr, &inst->handle) != VK_SUCCESS)
		log_critical("Failed to Create Instance.");

	log_info("The Instance was Created.");
}

void instance_destroy(const instance &inst) 
{
	log_info("Destroying the Instance...");

	if (inst.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Instance::Instance is not Created.");

	vkDestroyInstance(inst.handle, nullptr);

	log_info("The Instance was Destroyed.");
}
