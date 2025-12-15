#include "core/objects/Swapchain.hpp"
#include "core/objects/QueueFamily.hpp"
#include "util/debug/Logger.hpp"
#include "window/Window.hpp"

#include <limits>
#include <algorithm>

SwapchainSupportDetails swapchain_query_support_details(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface) {
    SwapchainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(phys_device, surface, &details.capabilities);
    uint32_t formats_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(phys_device, surface, &formatsCount, nullptr);
    if(formats_count != 0) {
        details.formats.resize(formats_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(phys_device, surface, &formats_count, details.formats.data());
    }
    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(phys_device, surface, &present_mode_count, nullptr);
    if(present_mode_count != 0) {
        details.presentModes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(phys_device, surface, &present_mode_count, details.presentModes.data());
    }
    return details;
}

bool swapchain_is_adequate(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface) {
    SwapchainSupportDetails details = swapchain_query_support_details(phys_device, surface);
    return !details.formats.empty() && !details.present_modes.empty();
}

VkSurfaceFormatKHR swapchain_choose_format(const std::vector<VkSurfaceFormatKHR>& formats) {
    Utils::Logger::get()->info("Choosing the Swapchain Format...");
    for(const auto& format : formats) {
        if(format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            Utils::Logger::get()->success("The Swapchain Format was Chosen!");
            return format;
        }
    }
    Utils::Logger::get()->success("The Swapchain Format was Chosen!");
    return formats[0];
}

VkPresentModeKHR swapchain_choose_present_mode(const std::vector<VkPresentModeKHR>& present_modes) {
    Utils::Logger::get()->info("Choosing the Swapchain Present Mode...");
    for(const auto& present_mode : present_modes) {
        if(present_mode == VK_PRESENT_MODE_MAILBOX_KHR) {
            Utils::Logger::get()->success("The Swapchain Present Mode was Chosen! Present Mode = VK_PRESENT_MODE_MAILBOX_KHR");
            return present_mode;
        }
    }
    Utils::Logger::get()->success("The Swapchain Present Mode was Chosen! Present Mode = VK_PRESENT_MODE_FIFO_KHR");
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D swapchain_choose_extent(const VkSurfaceCapabilitiesKHR& capabilities) {
    Utils::Logger::get()->info("Choosing the Swapchain Extent..."); 
    if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        Utils::Logger::get()->success("The Swapchain Extent was Chosen!");
        return capabilities.currentExtent;
    }
    else {
        int width, height;
        SDL_GetWindowSizeInPixels(Window::Window::get(), &width, &height); 
        VkExtent2D extent {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };
        extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
        Utils::Logger::get()->success("The Swapchain Extent was Chosen!");
        return extent;
    }
}

VkSwapchainCreateInfoKHR swapchain_create_info(
        const VkSurfaceKHR& surface, 
        const VkPhysicalDevice& phys_device, 
        const VkSurfaceFormatKHR& format, 
        const VkPresentModeKHR& present_mode, 
        const VkExtent2D& extent, 
        const VkSurfaceCapabilitiesKHR& capabilities, 
        uint32_t image_count
)
{
    Utils::Logger::get()->info("Creating the Swapchain Info...");
    VkSwapchainCreateInfoKHR create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.surface = surface;
    create_info.minImageCount = image_count;
    create_info.imageColorSpace = format.colorSpace;
    create_info.imageFormat = format.format;
    create_info.imageExtent = extent;
    create_info.imageArrayLayers = 1;
    create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    
    QueueFamily queue_family = queue_family_find(phys_device, surface);
    uint32_t queueFamilyIndices[] = {queue_family.graphics.has_value(), queue_family.present.has_value()};
    if(queue_family.graphics != queue_family.present) {
        create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        create_info.queueFamilyIndexCount = 2;
        create_info.pQueueFamilyIndices = queueFamilyIndices;
    }
    else {
        create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        create_info.queueFamilyIndexCount = 0;
        create_info.pQueueFamilyIndices = nullptr;
    }
    
    create_info.preTransform = capabilities.currentTransform;
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode = present_mode;
    create_info.clipped = VK_TRUE;
    create_info.oldSwapchain = VK_NULL_HANDLE;
    Utils::Logger::get()->success("The Swapchain Info was Created!");
    return create_info;
}

void swapchain_create(Swapchain* swapchain, const PhysicalDevice& phys_device, const LogicalDevice& device, const Surface& surface) {
    Utils::Logger::get()->info("Creating a Swapchain...");
    SwapchainSupportDetails details = querySupportDetails(physicalDevice.get(), surface.get());
    VkSurfaceFormatKHR surfaceFormat = chooseFormat(details.formats);
    VkPresentModeKHR presentMode = choosePresentMode(details.presentModes);
    VkExtent2D extent = chooseExtent(details.capabilities);
    uint32_t imageCount = details.capabilities.minImageCount + 1;
    
    if(details.capabilities.maxImageCount > 0 && imageCount > details.capabilities.maxImageCount)
        imageCount = details.capabilities.maxImageCount;
    
    VkSwapchainCreateInfoKHR swapchainInfo = createInfo(surface.get(), physicalDevice.get(), surfaceFormat, presentMode, extent, details.capabilities, imageCount);
    if(vkCreateSwapchainKHR(device.get(), &swapchainInfo, nullptr, &swapchain->handle) != VK_SUCCESS)
        Utils::Logger::get()->critical("Failed to Create the Swapchain!");
    Utils::Logger::get()->success("The Swapchain was Created!");
}

void swapchain_destroy(const LogicalDevice& device) {
    Utils::Logger::get()->info("Destroying the Swapchain...");
    if(swapchain.handle == VK_NULL_HANDLE)
        Utils::Logger::get()->error("Cannot Destroy the Swapchain::Swapchain is not Created!");
    vkDestroySwapchainKHR(device.handle, swapchain.handle, nullptr);

    Utils::Logger::get()->success("The Swapchain was Destroyed!");
}

VkExtent2D Engine::Core::Swapchain::extent()
{
    return actualExtent;
}
