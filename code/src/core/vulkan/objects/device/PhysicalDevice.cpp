#include "core/vulkan/objects/device/PhysicalDevice.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <map>
#include <set>

uint32_t phys_device_rate(const VkPhysicalDevice& phys_device) {
    VkPhysicalDeviceProperties phys_device_props;
    vkGetPhysicalDeviceProperties(phys_device, &phys_device_props);
    uint32_t score = 0;
    if(phys_device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 1000;
    }
    score += phys_device_props.limits.maxImageDimension2D;
    return score;
}

std::string phys_device_get_name(const VkPhysicalDevice& phys_device) {
    VkPhysicalDeviceProperties phys_device_props;
    vkGetPhysicalDeviceProperties(phys_device, &phys_device_props);
    return phys_device_props.deviceName;
}

bool phys_device_check_ext_support(const VkPhysicalDevice& phys_device) {
    uint32_t ext_count;
    vkEnumerateDeviceExtensionProperties(phys_device, nullptr, &ext_count, nullptr);
    
    std::vector<VkExtensionProperties> exts(ext_count);
    vkEnumerateDeviceExtensionProperties(phys_device, nullptr, &ext_count, exts.data());
    
    std::set<std::string> required_exts(phys_device_exts.begin(), phys_device_exts.end());
    for(const auto& ext : exts) {
        required_exts.erase(ext.extensionName);
    }
    return required_exts.empty();
}

bool phys_device_is_suitable(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface) {
    return phys_device_check_ext_support(phys_device) && swapchain_is_adequate(phys_device, surface);
}

void phys_device_pick(PhysicalDevice* phys_device, const Instance& instance, const Surface& surface) {
    log_info("Searching a Suitable GPU...");
    uint32_t phys_device_count = 0;
    vkEnumeratePhysicalDevices(instance.handle, &phys_device_count, nullptr);
    
    if(phys_device_count == 0) {
        log_critical("Failed to find GPU with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> phys_devices(phys_device_count);
    vkEnumeratePhysicalDevices(instance.handle, &phys_device_count, phys_devices.data());
    
    std::multimap<int, VkPhysicalDevice> candidates;
    for(const VkPhysicalDevice& phys_device : phys_devices) {
        uint32_t score = phys_device_rate(phys_device);
        candidates.insert(std::make_pair(score, phys_device));
    }
    if(candidates.rbegin()->first > 0) {
        phys_device->handle = candidates.rbegin()->second;
    }
    else if(!phys_device_is_suitable(phys_device->handle, surface.handle)) {
        log_critical("Failed to Find any Suitable GPU!");
    }
    else {
        log_critical("Failed to Find any Suitable GPU!");
    }
    log_success("The GPU was Found!");
    log_info("Selected GPU = ", phys_device_get_name(phys_device->handle));
}

VkPhysicalDeviceFeatures phys_device_get_features(const PhysicalDevice& phys_device) {
    VkPhysicalDeviceFeatures phys_device_features = {};
    vkGetPhysicalDeviceFeatures(phys_device.handle, &phys_device_features);
    if(phys_device_features.geometryShader != VK_TRUE) {
        log_critical("The found GPU doesn't have a Geometry Shader Feature!");
    }
    return phys_device_features;
}
