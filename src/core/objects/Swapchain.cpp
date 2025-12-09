#include "core/objects/Swapchain.hpp"
#include "core/objects/QueueFamily.hpp"
#include "util/debug/Logger.hpp"
#include "window/Window.hpp"

#include <limits>
#include <algorithm>

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
    for(const auto& format : availableFormats)
    {
        if(format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            return format;
    }

    return availableFormats[0];
}

VkPresentModeKHR Engine::Core::Swapchain::choosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    for(const auto& presentmode : availablePresentModes)
    {
        if(presentmode == VK_PRESENT_MODE_MAILBOX_KHR)
            return presentmode;
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Engine::Core::Swapchain::chooseExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
    if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    }

    else 
    {
        int width, height;
        SDL_GetWindowSizeInPixels(Window::Window::get(), &width, &height); 

        VkExtent2D actualExtent
        {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

VkSwapchainCreateInfoKHR Engine::Core::Swapchain::createInfo(const VkSurfaceKHR& surface, const VkPhysicalDevice& device, const VkSurfaceFormatKHR& format, const VkPresentModeKHR& presentMode, const VkExtent2D& extent, const VkSurfaceCapabilitiesKHR& capabilities, uint32_t imageCount)
{
    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageColorSpace = format.colorSpace;
    createInfo.imageFormat = format.format;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamily queue;

    Indices indices;
    indices = queue.find(device, surface);

    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.has_value(), indices.presentFamily.has_value()};

    if(indices.graphicsFamily != indices.presentFamily)
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }

    else 
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }

    createInfo.preTransform = capabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    return createInfo;
}

void Engine::Core::Swapchain::create(const PhysicalDevice& physicalDevice, const LogicalDevice& device, const Surface& surface)
{
    SwapchainSupportDetails details = querySupportDetails(physicalDevice.get(), surface.get());

    VkSurfaceFormatKHR surfaceFormat = chooseFormat(details.formats);
    VkPresentModeKHR presentMode = choosePresentMode(details.presentModes);
    VkExtent2D extent = chooseExtent(details.capabilities);

    uint32_t imageCount = details.capabilities.minImageCount + 1;

    if(details.capabilities.maxImageCount > 0 && imageCount > details.capabilities.maxImageCount)
        imageCount = details.capabilities.maxImageCount;

    VkSwapchainCreateInfoKHR swapchainInfo = createInfo(surface.get(), physicalDevice.get(), surfaceFormat, presentMode, extent, details.capabilities, imageCount);

    if(vkCreateSwapchainKHR(device.get(), &swapchainInfo, nullptr, &swapchain) != VK_SUCCESS)
        Utils::Logger::get()->critical("Failed to Create the Swapchain!");
}

void Engine::Core::Swapchain::destroy(const LogicalDevice& device)
{
    vkDestroySwapchainKHR(device.get(), swapchain, nullptr);
}