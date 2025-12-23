#include "core/vulkan/objects/LogicalDevice.hpp"
#include "core/vulkan/objects/PhysicalDevice.hpp"
#include "core/vulkan/objects/QueueFamily.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>

VkDeviceQueueCreateInfo device_create_queue_info(const QueueFamily& queue_family) {
    log_info("Creating the Queue Info..."); 
    VkDeviceQueueCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    create_info.queueFamilyIndex = queue_family.graphics.value();
    create_info.queueCount = 1;
    const float queuePriority = 1.0f;
    create_info.pQueuePriorities = &queuePriority;
    log_success("The Queue Info was Created!");
    return create_info;
}

VkDeviceCreateInfo device_create_info(const PhysicalDevice& phys_device, const VkDeviceQueueCreateInfo& queue_info, VkPhysicalDeviceFeatures* phys_device_features) 
{
    log_info("Creating the Logical Device Info...");
    VkDeviceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.pQueueCreateInfos = &queue_info;
    create_info.queueCreateInfoCount = 1;
    phys_device_features->geometryShader = phys_device_get_features(phys_device).geometryShader;
    create_info.pEnabledFeatures = phys_device_features;
    create_info.enabledExtensionCount = static_cast<uint32_t>(phys_device_exts.size());
    create_info.ppEnabledExtensionNames = phys_device_exts.data();
    create_info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    create_info.ppEnabledLayerNames = validationLayers.data();
    log_success("The Logical Device Info was Created!");
    return create_info;
}

void device_create(LogicalDevice* device, Queue* queue, const QueueFamily& queue_family, const PhysicalDevice& phys_device) {
    log_info("Creating a Logical Device...");
    VkPhysicalDeviceFeatures features = {};
    VkDeviceQueueCreateInfo queue_info = device_create_queue_info(queue_family);
    VkDeviceCreateInfo device_info = device_create_info(phys_device, queue_info, &features);
    
    if(vkCreateDevice(phys_device.handle, &device_info, nullptr, &device->handle) != VK_SUCCESS) {
        log_critical("Failed to Create the Logical Device!");
    }
    vkGetDeviceQueue(device->handle, queue_family.graphics.value(), 0, &queue->graphics);
    vkGetDeviceQueue(device->handle, queue_family.present.value(), 0, &queue->present);
    log_success("The Logical Device was created!");
}

void device_destroy(const LogicalDevice& device) {
    log_info("Destroying the Logical Device...");
    
    if(device.handle == VK_NULL_HANDLE) {
        log_error("Cannot Destroy the Logical Device::Logical Device is not Created!");
    }
    vkDestroyDevice(device.handle, nullptr);
    
    log_success("The Logical Device was Destroyed!");
}
