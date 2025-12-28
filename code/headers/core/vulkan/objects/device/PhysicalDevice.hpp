#pragma once

#include "core/vulkan/objects/instance/Surface.hpp"
#include "core/vulkan/objects/instance/Instance.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>
#include <string>
#include <vector>

struct PhysicalDevice {
    VkPhysicalDevice handle = VK_NULL_HANDLE;
};

const std::vector<const char*> phys_device_exts = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

uint32_t phys_device_rate(const VkPhysicalDevice& phys_device);

std::string phys_device_get_name(const VkPhysicalDevice& phys_device);

bool phys_device_check_ext_support(const VkPhysicalDevice& phys_device);

bool phys_device_is_suitable(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface);

void phys_device_pick(PhysicalDevice* phys_device, const Instance& instance, const Surface& surface);

VkPhysicalDeviceFeatures phys_device_get_features(const PhysicalDevice& phys_device);
