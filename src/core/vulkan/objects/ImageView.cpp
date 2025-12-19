#include "core/vulkan/objects/ImageView.hpp"
#include "util/debug/Logger.hpp"

VkImageViewCreateInfo image_view_create_info(const VkImage& image, const VkFormat& format) {
    log_info("Creating the Image View Info...");
    
    VkImageViewCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    create_info.image = image;
    create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    create_info.format = format;
    create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    create_info.subresourceRange.baseMipLevel = 0;
    create_info.subresourceRange.levelCount = 1;
    create_info.subresourceRange.baseArrayLayer = 0;
    create_info.subresourceRange.layerCount = 1;
        
    log_success("The Image View Info was Created!");
    return create_info;
}

void image_view_create(Swapchain* swapchain, const LogicalDevice& device) {
    log_info("Creating an Image View...");
    
    uint32_t image_count = 0;
    vkGetSwapchainImagesKHR(device.handle, swapchain->handle, &image_count, nullptr);

    swapchain->images.resize(image_count);
    vkGetSwapchainImagesKHR(device.handle, swapchain->handle, &image_count, swapchain->images.data());
    
    swapchain->views.resize(swapchain->images.size());
    for(uint32_t i = 0; i < swapchain->images.size(); ++i) {
        VkImageViewCreateInfo image_view_info = image_view_create_info(swapchain->images[i], swapchain->format);
        if(vkCreateImageView(device.handle, &image_view_info, nullptr, &swapchain->views[i]) != VK_SUCCESS) {
            log_critical("Failed to Create the ImageView!");
        }
    }
    log_success("The Image View was Created!");
}

void image_view_destroy(const Swapchain& swapchain, const LogicalDevice& device) {
    log_info("Destroying the Image View...");
    for(auto& view : swapchain.views) {
        vkDestroyImageView(device.handle, view, nullptr);
    }
    log_success("The Image View was Destroyed!");
}
