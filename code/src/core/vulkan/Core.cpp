#include "core/vulkan/Core.hpp"
#include "core/vulkan/objects/swapchain/ImageView.hpp"
#include "core/vulkan/objects/swapchain/Framebuffer.hpp"
#include "util/debug/Logger.hpp"

void vk_core_init(Core* vk_core, const Window& window) {
    log_info("Initializing a Core...");
    instance_create(&vk_core->instance);
    debug_msgr_setup(&vk_core->debug_msgr, vk_core->instance);
    surface_create(&vk_core->surface, vk_core->instance, window);
    phys_device_pick(&vk_core->phys_device, vk_core->instance, vk_core->surface);
    queue_family_find(&vk_core->queue_family, vk_core->phys_device, vk_core->surface);
    device_create(&vk_core->device, &vk_core->queue, vk_core->queue_family, vk_core->phys_device);
    swapchain_create(&vk_core->swapchain, vk_core->device, vk_core->phys_device, vk_core->queue_family, window, vk_core->surface);
    img_view_create(&vk_core->swapchain, vk_core->device);
    pipeline_layout_create(&vk_core->pipeline_layout, vk_core->device);
    render_pass_create(&vk_core->render_pass, vk_core->device, vk_core->swapchain);
    pipeline_create(&vk_core->pipeline, vk_core->device, vk_core->swapchain, vk_core->pipeline_layout, vk_core->render_pass);
    framebuffer_create(&vk_core->swapchain, vk_core->device, vk_core->render_pass);
    command_pool_create(&vk_core->command_pool, vk_core->device, vk_core->queue_family);
    command_buffers_create(&vk_core->command_buffers, vk_core->device, vk_core->command_pool);
    semaphores_create(&vk_core->img_available_semaphores, vk_core->device);
    semaphores_create(&vk_core->render_finished_semaphores, vk_core->device);
    fences_create(&vk_core->in_flight_fences, vk_core->device);
    log_success("The Core was Initialized!");
}

void vk_core_destroy(Core* vk_core) {
    log_info("Destroying the Core...");
    fences_destroy(vk_core->in_flight_fences, vk_core->device);
    semaphores_destroy(vk_core->render_finished_semaphores, vk_core->device);
    semaphores_destroy(vk_core->img_available_semaphores, vk_core->device);
    command_pool_destroy(vk_core->command_pool, vk_core->device);
    framebuffer_destroy(vk_core->swapchain, vk_core->device);
    pipeline_destroy(vk_core->pipeline, vk_core->device);
    render_pass_destroy(&vk_core->render_pass, vk_core->device);
    pipeline_layout_destroy(vk_core->pipeline_layout, vk_core->device);
    img_view_destroy(vk_core->swapchain, vk_core->device);
    swapchain_destroy(vk_core->swapchain, vk_core->device);
    device_destroy(vk_core->device);
    surface_destroy(vk_core->surface, vk_core->instance);
    debug_msgr_destroy(&vk_core->debug_msgr, vk_core->instance);
    instance_destroy(vk_core->instance);
    log_success("The Core was Destroyed!");
}
