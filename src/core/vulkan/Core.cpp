#include "core/vulkan/Core.hpp"
#include "core/vulkan/objects/PhysicalDevice.hpp"
#include "core/vulkan/objects/Pipeline.hpp"
#include "core/vulkan/objects/RenderPass.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"

void vk_core_init(Core* vk_core, const Window& window) {
    log_info("Initializing a Core...");
    instance_create(&vk_core->instance);
    debug_msgr_setup(&vk_core->debug_msgr, vk_core->instance);
    surface_create(&vk_core->surface, vk_core->instance, window);
    phys_device_pick(&vk_core->phys_device, vk_core->instance, vk_core->surface);
    device_create(&vk_core->device, vk_core->phys_device, vk_core->surface);
    swapchain_create(&vk_core->swapchain, vk_core->phys_device, vk_core->device, window, vk_core->surface);
    image_view_create(&vk_core->image_view, vk_core->device);
    pipeline_layout_create(&vk_core->pipeline_layout, vk_core->device);
    render_pass_create(&vk_core->render_pass, vk_core->device, vk_core->image_view);
    pipeline_create(&vk_core->pipeline, vk_core->device, vk_core->swapchain, vk_core->pipeline_layout, vk_core->render_pass);
    log_success("The Core was Initialized!");
}

void vk_core_destroy(Core* vk_core) {
    log_info("Destroying the Core...");
    pipeline_destroy(vk_core->pipeline, vk_core->device);
    render_pass_destroy(&vk_core->render_pass, vk_core->device);
    pipeline_layout_destroy(vk_core->pipeline_layout, vk_core->device);
    image_view_destroy(vk_core->image_view, vk_core->device);
    swapchain_destroy(vk_core->swapchain, vk_core->device);
    device_destroy(vk_core->device);
    phys_device_pick(&vk_core->phys_device, vk_core->instance, vk_core->surface);
    surface_destroy(vk_core->surface, vk_core->instance);
    debug_msgr_destroy(&vk_core->debug_msgr, vk_core->instance);
    instance_destroy(vk_core->instance);
    log_success("The Core was Destroyed!");
}
