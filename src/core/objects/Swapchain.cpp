#include "core/objects/Swapchain.hpp"

Engine::Core::SwapchainSupportDetails Engine::Core::Swapchain::querySupportDetails(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
{
    SwapchainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);
    
    uint32_t formatsCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatsCount, nullptr);

    if(formatsCount != 0)
    {
        details.formats.resize(formatsCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatsCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if(presentModeCount != 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

bool Engine::Core::Swapchain::isAdequate(const VkPhysicalDevice &device, const VkSurfaceKHR& surface)
{
    SwapchainSupportDetails details = querySupportDetails(device, surface);
    return !details.formats.empty() && !details.presentModes.empty();
}

VkSurfaceFormatKHR Engine::Core::Swapchain::chooseFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{

}

VkSurfacePresentModeKHR Engine::Core::Swapchain::choosePresentMode(const std::vector<VkSurfacePresentModeKHR>& availablePresentModes)
{

}