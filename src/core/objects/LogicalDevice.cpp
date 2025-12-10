#include "core/objects/LogicalDevice.hpp"
#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/QueueFamily.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>

VkDeviceQueueCreateInfo Engine::Core::LogicalDevice::createQueueInfo(const PhysicalDevice& physicalDevice, const Surface& surface)
{
    Utils::Logger::get()->info("Creating the Queue Info..."); 

    Indices indices;
    indices = QueueFamily::find(physicalDevice.get(), surface.get());

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    const float queuePriority = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    Utils::Logger::get()->success("The Queue Info was Created!");

    return queueCreateInfo;
}

VkDeviceCreateInfo Engine::Core::LogicalDevice::createInfo(PhysicalDevice& physicalDevice, const VkDeviceQueueCreateInfo& queueInfo, VkPhysicalDeviceFeatures* physicalDeviceFeatures)
{
    Utils::Logger::get()->info("Creating the Logical Device Info...");

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueInfo;
    createInfo.queueCreateInfoCount = 1;

    VkPhysicalDeviceFeatures features = physicalDevice.features();
    physicalDeviceFeatures->geometryShader = features.geometryShader;
    
    createInfo.pEnabledFeatures = physicalDeviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(Core::physicalDeviceExtensions.size());
    createInfo.ppEnabledExtensionNames = Core::physicalDeviceExtensions.data();

    createInfo.enabledLayerCount = static_cast<uint32_t>(Utils::validationLayers.size());
    createInfo.ppEnabledLayerNames = Utils::validationLayers.data();

    Utils::Logger::get()->success("The Logical Device Info was Created!");

    return createInfo;
}

void Engine::Core::LogicalDevice::create(PhysicalDevice& physicalDevice, const Surface& surface)
{
    Utils::Logger::get()->info("Creating a Logical Device...");

    VkPhysicalDeviceFeatures enabledDeviceFeatures = {};

    VkDeviceQueueCreateInfo queueInfo = createQueueInfo(physicalDevice, surface);
    VkDeviceCreateInfo deviceInfo = createInfo(physicalDevice, queueInfo, &enabledDeviceFeatures);

    if(vkCreateDevice(physicalDevice.get(), &deviceInfo, nullptr, &device) != VK_SUCCESS)
        Utils::Logger::get()->critical("Failed to Create the Logical Device!");

    Utils::Logger::get()->success("The Logical Device was created!");
}

void Engine::Core::LogicalDevice::destroy()
{
    Utils::Logger::get()->info("Destroying the Logical Device...");

    if(device == VK_NULL_HANDLE)
        Utils::Logger::get()->error("Cannot Destroy the Logical Device::Logical Device is not Created!");

    vkDestroyDevice(device, nullptr);

    Utils::Logger::get()->success("The Logical Device was Destroyed!");
}

VkDevice Engine::Core::LogicalDevice::get() const
{
    return device;
}
