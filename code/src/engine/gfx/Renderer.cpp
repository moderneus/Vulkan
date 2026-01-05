#include "engine/gfx/Renderer.hpp"
#include "engine/window/Window.hpp"
#include "core/vulkan/Core.hpp"
#include "util/EventManager.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

#include <vulkan/vulkan.h>

#include <array>

uint32_t current_frame = 0;

void renderer_init(Renderer* renderer, Window* pwindow) {
    log_info("Initializing a Renderer...");
    renderer->pwindow = pwindow;
    log_success("The Renderer was Initialized!");
}

void renderer_destroy(Renderer* renderer) {
    log_info("Destroying the Renderer...");
    renderer->pwindow = nullptr;
    log_success("The Renderer was Destroyed!");
}

void renderer_loop(Renderer* renderer, const Core* vk_core) {
    while(!renderer->pwindow->is_closed) {
        event_manager_poll_events(&renderer->event_manager, renderer->pwindow);
        renderer_draw(vk_core);
    }
    vkDeviceWaitIdle(vk_core->device.handle);
}

void renderer_draw(const Core* vk_core) {
    vkWaitForFences(vk_core->device.handle, 1, &vk_core->in_flight_fences[current_frame].handle, VK_TRUE, UINT64_MAX);
    vkResetFences(vk_core->device.handle, 1, &vk_core->in_flight_fences[current_frame].handle);

    uint32_t img_idx;
    vkAcquireNextImageKHR(vk_core->device.handle, vk_core->swapchain.handle, UINT64_MAX, vk_core->img_available_semaphores[current_frame].handle, VK_NULL_HANDLE, &img_idx);

    vkResetCommandBuffer(vk_core->command_buffers[current_frame].handle, 0);
    command_buffer_record(vk_core->command_buffers[current_frame], vk_core->pipeline, vk_core->render_pass, vk_core->swapchain, img_idx);

    std::array<VkSemaphore, 1> wait_semaphores = {vk_core->img_available_semaphores[current_frame].handle};
    std::array<VkPipelineStageFlags, 1> wait_stages = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    std::array<VkSemaphore, 1> signal_semaphores = {vk_core->render_finished_semaphores[current_frame].handle};
    
    VkSubmitInfo submit_info = queue_create_submit_info(current_frame, wait_semaphores, signal_semaphores, wait_stages, vk_core->command_buffers);
    
    if(vkQueueSubmit(vk_core->queue.graphics, 1, &submit_info, vk_core->in_flight_fences[current_frame].handle) != VK_SUCCESS) {
        log_critical("Failed to Submit Draw Command Buffer!");
    }
    std::array<VkSwapchainKHR, 1> swapchains = {vk_core->swapchain.handle};
    VkPresentInfoKHR present_info = queue_create_present_info(signal_semaphores, swapchains, img_idx);
    
    vkQueuePresentKHR(vk_core->queue.present, &present_info);
    
    current_frame = (current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}
