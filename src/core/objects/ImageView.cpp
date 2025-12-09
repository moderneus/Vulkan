#include "core/objects/ImageView.hpp"
#include "util/debug/Logger.hpp"

VkImageViewCreateInfo Engine::Core::ImageView::createInfo()
{
    Utils::Logger::get()->info("Creating the Image View Info...");
    
    swapchainImageViews.resize(swapchainImages.size());
    
    VkImageViewCreateInfo createInfo = {};

    for(const auto& image : swapchainImages)
    {
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = image;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        createInfo.format = swapchainImageFormat;
        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;
    }

    Utils::Logger::get()->success("The Image View Info was Created!");

    return createInfo;
}

void Engine::Core::ImageView::create(const LogicalDevice& device)
{
    Utils::Logger::get()->info("Creating an Image View...");
    
    for(auto& imageView : swapchainImageViews)
    {
        VkImageViewCreateInfo imageViewInfo = createInfo();

        if(vkCreateImageView(device.get(), &imageViewInfo, nullptr, &imageView) != VK_SUCCESS)
            Utils::Logger::get()->critical("Failed to Create the ImageView!");
    }

    Utils::Logger::get()->success("The Image View was Created!");
}

void Engine::Core::ImageView::destroy(const LogicalDevice& device)
{
    Utils::Logger::get()->info("Destroying the Image View...");
    
    for(auto& imageView : swapchainImageViews)
    {
        if(imageView == VK_NULL_HANDLE)
            Utils::Logger::get()->error("Cannot Destroy the Image View::Image View is not Created!");
        
        vkDestroyImageView(device.get(), imageView, nullptr);
    }

    Utils::Logger::get()->success("The Image View was Destroyed!");
}

VkImageView Engine::Core::ImageView::get() const
{
    return imageView;
}
