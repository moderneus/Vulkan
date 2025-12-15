#include "core/objects/LogicalDevice.hpp"
#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/QueueFamily.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>

VkDeviceQueueCreateInfo device_create_queue_info(const PhysicalDevice& phys_device, const Surface& surface) {
    Utils::Logger::get()->info("Creating the Queue Info..."); 
    VkDeviceQueueCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    QueueFamily queue_family = queue_family_find(phys_device.handle, surface.handle);
    create_info.queueFamilyIndex = queue_family.graphicsFamily.value();
    create_info.queueCount = 1;
    const float queuePriority = 1.0f;
    create_info.pQueuePriorities = &queuePriority;
    Utils::Logger::get()->success("The Queue Info was Created!");
    return create_info;
}

VkDeviceCreateInfo device_create_info(
    PhysicalDevice& phys_device, 
    const VkDeviceQueueCreateInfo& queue_info, 
    VkPhysicalDeviceFeatures* phys_device_features
) 
{
    Utils::Logger::get()->info("Creating the Logical Device Info...");
    VkDeviceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.pQueueCreateInfos = &queue_info;
    create_info.queueCreateInfoCount = 1;
    VkPhysicalDeviceFeatures features = phys_device_get_features();
    phys_device_features->geometryShader = features.geometryShader;
    create_info.pEnabledFeatures = phys_device_features;
    create_info.enabledExtensionCount = static_cast<uint32_t>(Core::physicalDeviceExtensions.size());
    create_info.ppEnabledExtensionNames = Core::physicalDeviceExtensions.data();
    create_info.enabledLayerCount = static_cast<uint32_t>(Utils::validationLayers.size());
    create_info.ppEnabledLayerNames = Utils::validationLayers.data();
    Utils::Logger::get()->success("The Logical Device Info was Created!");
    return create_info;
}

void device_create(LogicalDevice* device, PhysicalDevice& phys_device, const Surface& surface) {
    Utils::Logger::get()->info("Creating a Logical Device...");
    VkPhysicalDeviceFeatures features = {};
    VkDeviceQueueCreateInfo queue_info = device_create_queue_info(phys_device, surface);
    VkDeviceCreateInfo device_info = device_create_info(phys_device, queue_info, &features);
    if(vkCreateDevice(phys_device.handle, &device_info, nullptr, &device->handle) != VK_SUCCESS)
        Utils::Logger::get()->critical("Failed to Create the Logical Device!");
    Utils::Logger::get()->success("The Logical Device was created!");
}

void device_destroy(const LogicalDevice& device) {
    Utils::Logger::get()->info("Destroying the Logical Device...");
    if(device.handle == VK_NULL_HANDLE)
        Utils::Logger::get()->error("Cannot Destroy the Logical Device::Logical Device is not Created!");
    vkDestroyDevice(device.handle, nullptr);
    Utils::Logger::get()->success("The Logical Device was Destroyed!");
}
