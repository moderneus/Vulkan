#include "core/objects/Swapchain.hpp"
#include "core/objects/QueueFamily.hpp"
#include "util/debug/Logger.hpp"
#include "window/Window.hpp"

#include <limits>
#include <algorithm>

Engine::Core::SwapchainSupportDetails Engine::Core::Swapchain::querySupportDetails(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface)
{
    SwapchainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);
    
    uint32_t formatsCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatsCount, nullptr);

    if(formatsCount != 0)
    {
        details.formats.resize(formatsCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatsCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

    if(presentModeCount != 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}

bool Engine::Core::Swapchain::isAdequate(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface)
{
    SwapchainSupportDetails details = querySupportDetails(physicalDevice, surface);
    return !details.formats.empty() && !details.presentModes.empty();
}

VkSurfaceFormatKHR Engine::Core::Swapchain::chooseFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
    Utils::Logger::get()->info("Choosing the Swapchain Format...");
    
    for(const auto& format : availableFormats)
    {
        if(format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            Utils::Logger::get()->success("The Swapchain Format was Chosen!");
            return format;
        }
    }

    Utils::Logger::get()->success("The Swapchain Format was Chosen!");

    return availableFormats[0];
}

VkPresentModeKHR Engine::Core::Swapchain::choosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
    Utils::Logger::get()->info("Choosing the Swapchain Present Mode...");
    
    for(const auto& presentmode : availablePresentModes)
    {
        if(presentmode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            Utils::Logger::get()->success("The Swapchain Present Mode was Chosen! Present Mode = VK_PRESENT_MODE_MAILBOX_KHR");
            return presentmode;
        }
    }

    Utils::Logger::get()->success("The Swapchain Present Mode was Chosen! Present Mode = VK_PRESENT_MODE_FIFO_KHR");

    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Engine::Core::Swapchain::chooseExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
    Utils::Logger::get()->info("Choosing the Swapchain Extent...");
    
    if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        Utils::Logger::get()->success("The Swapchain Extent was Chosen!");
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

        Utils::Logger::get()->success("The Swapchain Extent was Chosen!");

        return actualExtent;
    }
}

VkSwapchainCreateInfoKHR Engine::Core::Swapchain::createInfo
(
        const VkSurfaceKHR& surface, 
        const VkPhysicalDevice& physicalDevice, 
        const VkSurfaceFormatKHR& format, 
        const VkPresentModeKHR& presentMode, 
        const VkExtent2D& extent, 
        const VkSurfaceCapabilitiesKHR& capabilities, 
        uint32_t imageCount
)
{
    Utils::Logger::get()->info("Creating the Swapchain Info...");

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
    indices = queue.find(physicalDevice, surface);

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

    Utils::Logger::get()->success("The Swapchain Info was Created!");

    return createInfo;
}

void Engine::Core::Swapchain::create(const PhysicalDevice& physicalDevice, const LogicalDevice& device, const Surface& surface)
{
    Utils::Logger::get()->info("Creating a Swapchain...");
    
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

    Utils::Logger::get()->success("The Swapchain was Created!");
}

void Engine::Core::Swapchain::destroy(const LogicalDevice& device)
{
    Utils::Logger::get()->info("Destroying the Swapchain...");
    
    if(swapchain == VK_NULL_HANDLE)
        Utils::Logger::get()->error("Cannot Destroy the Swapchain::Swapchain is not Created!");
        
    vkDestroySwapchainKHR(device.get(), swapchain, nullptr);

    Utils::Logger::get()->success("The Swapchain was Destroyed!");
}
