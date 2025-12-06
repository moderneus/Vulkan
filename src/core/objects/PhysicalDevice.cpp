#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/QueueFamily.hpp"
#include "core/objects/Swapchain.hpp"
#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <map>
#include <set>

int Engine::Core::PhysicalDevice::rate(const VkPhysicalDevice& device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    
    int score = 0;
    if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;

    score += deviceProperties.limits.maxImageDimension2D;
    
    return score;
}

std::string Engine::Core::PhysicalDevice::name(const VkPhysicalDevice& device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    return deviceProperties.deviceName;
}

bool Engine::Core::PhysicalDevice::checkExtensionSupport(const VkPhysicalDevice& device)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for(const auto& extension : availableExtensions)
        requiredExtensions.erase(extension.extensionName);

    return requiredExtensions.empty();
}

bool Engine::Core::PhysicalDevice::isSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
{
    QueueFamily queueFamily;
    queueFamily.find(device);

    return checkExtensionSupport(device) && Swapchain::isAdequate(device, surface);
}

void Engine::Core::PhysicalDevice::pick(const Surface& surface)
{
    Utils::Logger::get()->info("Searching a Suitable GPU...");

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(Core::Core::get()->getInstance(), &deviceCount, nullptr);

    if(deviceCount == 0)
        Utils::Logger::get()->critical("Failed to find GPU with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(Core::Core::get()->getInstance(), &deviceCount, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;

    for(const VkPhysicalDevice& device : devices)
    {
        int score = rate(device);
        candidates.insert(std::make_pair(score, device));
    }

    if(candidates.rbegin()->first > 0)
        physicalDevice = candidates.rbegin()->second;

    else if(!isSuitable(physicalDevice, surface.get()))
        Utils::Logger::get()->critical("Failed to Find any Suitable GPU!");

    else
        Utils::Logger::get()->critical("Failed to Find any Suitable GPU!");

    Utils::Logger::get()->success("The GPU was Found!");
    Utils::Logger::get()->info("Selected GPU = ", name(physicalDevice));
}

VkPhysicalDeviceFeatures Engine::Core::PhysicalDevice::features()
{
    VkPhysicalDeviceFeatures deviceFeatures = {};
    vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

    if(deviceFeatures.geometryShader != VK_TRUE)
        Utils::Logger::get()->critical("The found GPU doesn't have Geometry Shader Feature!");

    return deviceFeatures;
}

VkPhysicalDevice Engine::Core::PhysicalDevice::get() const
{
    return physicalDevice;
}