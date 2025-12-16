#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

void vk_core_init(Core* vk_core) {
    log_info("Initializing a Core...");
    instance_create(&vk_core->instance);
    surface_create();
    phys_device_pick(vk_core->surface);
    device_create(&vk_core->device, vk_core->phys_device, vk_core->surface);
    swapchain_create(&vk_core->swapchain, vk_core->phys_device, vk_core->device, vk_core->surface);
    image_view_create(&vk_core->image_view, vk_core->device);
    pipeline_layout_create(vk_core->device);
    pipeline_create(vk_core->device, vk_core->swapchain);
    log_success("The Core was Initialized!");
}

void vk_core_destroy(Core* vk_core) {
    log_info("Destroying the Core...");
    pipeline_destroy(vk_core->device);
    pipeline_layout_destroy(vk_core->device);
    image_view_destroy(&vk_core->image_view, vk_core->device);
    swapchain_destroy(vk_core->swapchain, vk_core->device);
    device_destroy(vk_core->device);
    surface_destroy();
    instance_destroy(vk_core->instance);
    log_success("The Core was Destroyed!");
}
