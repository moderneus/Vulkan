#include "core/objects/QueueFamily.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstdint>

bool queue_family_is_complete(const QueueFamily& queue_family) {
    return queue_family.graphics.has_value() && queue_family.present.has_value();
}

QueueFamily queue_family_find(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface) {
    log_info("Seacrhing a Suitable Queue Families...");
    
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(phys_device, &queue_family_count, nullptr);
    
    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(phys_device, &queue_family_count, queue_families.data());

    QueueFamily queue_family;
    for (uint32_t i = 0; i < queue_family_count ; ++i) {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queue_family.graphics = i;
        }
        
        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(phys_device, i, surface, &present_support);
        
        if(present_support) {
            queue_family.present = i;
        }
        if(queue_family_is_complete(queue_family)) {
            break;
        }
    }
    if(!queue_family_is_complete(queue_family)) {
        log_critical("Failed to Find any Suitable Queue Families!");
    }
    log_success("The Suitable Queue Families was Found!");
    return queue_family;
}
