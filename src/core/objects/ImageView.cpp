#include "core/objects/ImageView.hpp"
#include "util/debug/Logger.hpp"

VkImageViewCreateInfo image_view_create_info(ImageView* image_view) {
    Utils::Logger::get()->info("Creating the Image View Info...");
    image_view->views.resize(image_view->images.size());
    VkImageViewCreateInfo create_info = {};
    for(const auto& image : image_view->images) {
        create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        create_info.image = image;
        create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        create_info.format = image_view->format;
        create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        create_info.subresourceRange.baseMipLevel = 0;
        create_info.subresourceRange.levelCount = 1;
        create_info.subresourceRange.baseArrayLayer = 0;
        create_info.subresourceRange.layerCount = 1;
    }
    Utils::Logger::get()->success("The Image View Info was Created!");
    return create_info;
}

void image_view_create(ImageView* image_view, const LogicalDevice& device) {
    Utils::Logger::get()->info("Creating an Image View...");
    for(auto& view : image_view->views) {
        VkImageViewCreateInfo image_view_info = image_view_create_info(image_view);
        if(vkCreateImageView(device.handle, &image_view_info, nullptr, &view) != VK_SUCCESS)
            Utils::Logger::get()->critical("Failed to Create the ImageView!");
    }
    Utils::Logger::get()->success("The Image View was Created!");
}

void image_view_destroy(const ImageView& image_view, const LogicalDevice& device) {
    Utils::Logger::get()->info("Destroying the Image View...");
    for(auto& view : image_view.views) {
        if(image_view.handle == VK_NULL_HANDLE)
            Utils::Logger::get()->error("Cannot Destroy the Image View::Image View is not Created!");
        vkDestroyImageView(device.handle, image_view.handle, nullptr);
    }
    Utils::Logger::get()->success("The Image View was Destroyed!");
}
