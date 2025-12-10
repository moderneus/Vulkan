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

int Engine::Core::PhysicalDevice::rate(const VkPhysicalDevice& physicalDevice)
{
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
    
    int score = 0;
    if(physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;

    score += physicalDeviceProperties.limits.maxImageDimension2D;
    
    return score;
}

std::string Engine::Core::PhysicalDevice::name(const VkPhysicalDevice& physicalDevice)
{
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

    return physicalDeviceProperties.deviceName;
}

bool Engine::Core::PhysicalDevice::checkExtensionSupport(const VkPhysicalDevice& physicalDevice)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(physicalDeviceExtensions.begin(), physicalDeviceExtensions.end());

    for(const auto& extension : availableExtensions)
        requiredExtensions.erase(extension.extensionName);

    return requiredExtensions.empty();
}

bool Engine::Core::PhysicalDevice::isSuitable(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface)
{
    QueueFamily::find(physicalDevice, surface);

    return checkExtensionSupport(physicalDevice) && Swapchain::isAdequate(physicalDevice, surface);
}

void Engine::Core::PhysicalDevice::pick(const Surface& surface)
{
    Utils::Logger::get()->info("Searching a Suitable GPU...");

    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(Core::Core::get()->getInstance(), &physicalDeviceCount, nullptr);

    if(physicalDeviceCount == 0)
        Utils::Logger::get()->critical("Failed to find GPU with Vulkan support!");

    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(Core::Core::get()->getInstance(), &physicalDeviceCount, physicalDevices.data());

    std::multimap<int, VkPhysicalDevice> candidates;

    for(const VkPhysicalDevice& physicalDevice : physicalDevices)
    {
        int score = rate(physicalDevice);
        candidates.insert(std::make_pair(score, physicalDevice));
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
    VkPhysicalDeviceFeatures physicalDeviceFeatures = {};
    vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

    if(physicalDeviceFeatures.geometryShader != VK_TRUE)
        Utils::Logger::get()->critical("The found GPU doesn't have Geometry Shader Feature!");

    return physicalDeviceFeatures;
}

VkPhysicalDevice Engine::Core::PhysicalDevice::get() const
{
    return physicalDevice;
}
