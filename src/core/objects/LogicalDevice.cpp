#include "core/objects/LogicalDevice.hpp"
#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/QueueFamily.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>

VkDeviceQueueCreateInfo Engine::Core::LogicalDevice::createQueueInfo(const PhysicalDevice& device)
{
    Utils::Logger::get()->info("Creating the Queue Info...");
    
    QueueFamily queueFamily;
    uint32_t indices = queueFamily.find(device.get());

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices;
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    Utils::Logger::get()->success("The Queue Info was Created!");

    return queueCreateInfo;
}

VkDeviceCreateInfo Engine::Core::LogicalDevice::createInfo(PhysicalDevice& device, const VkDeviceQueueCreateInfo& queueInfo, VkPhysicalDeviceFeatures* deviceFeatures)
{
    Utils::Logger::get()->info("Creating the Logical Device Info...");

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueInfo;
    createInfo.queueCreateInfoCount = 1;

    VkPhysicalDeviceFeatures physicalDeviceFeatures = device.features();
    deviceFeatures->geometryShader = physicalDeviceFeatures.geometryShader;
    
    createInfo.pEnabledFeatures = deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(Core::deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = Core::deviceExtensions.data();

    createInfo.enabledLayerCount = static_cast<uint32_t>(Utils::validationLayers.size());
    createInfo.ppEnabledLayerNames = Utils::validationLayers.data();

    Utils::Logger::get()->success("The Logical Device Info was Created!");

    return createInfo;
}

void Engine::Core::LogicalDevice::create(PhysicalDevice& device)
{
    Utils::Logger::get()->info("Creating a Logical Device...");

    VkPhysicalDeviceFeatures enabledDeviceFeatures = {};

    VkDeviceQueueCreateInfo queueInfo = createQueueInfo(device);
    VkDeviceCreateInfo logicalDeviceInfo = createInfo(device, queueInfo, &enabledDeviceFeatures);

    if(vkCreateDevice(device.get(), &logicalDeviceInfo, nullptr, &logicalDevice) != VK_SUCCESS)
        Utils::Logger::get()->critical("Failed to Create the Logical Device!");

    Utils::Logger::get()->success("The Logical Device was created!");
}

void Engine::Core::LogicalDevice::destroy()
{
    Utils::Logger::get()->info("Destroying the Logical Device...");

    if(logicalDevice == VK_NULL_HANDLE)
        Utils::Logger::get()->error("Cannot Destroy the Logical Device::Logical Device is not Created!");

    vkDestroyDevice(logicalDevice, nullptr);

    Utils::Logger::get()->success("The Logical Device was Destroyed!");
}

VkDevice Engine::Core::LogicalDevice::get() const
{
    return logicalDevice;
}