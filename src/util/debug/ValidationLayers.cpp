#include "util/debug/ValidationLayers.hpp"

#include <vulkan/vulkan.h>

#include <cstring>
#include <vector>

const std::vector<const char*> Engine::Utils::ValidationLayers::validationLayers = {"VK_LAYER_KHRONOS_validation"};

const std::vector<const char*>& Engine::Utils::ValidationLayers::get()
{
    return validationLayers;
}

void Engine::Utils::ValidationLayers::enable()
{
    debugging = true;
}

bool Engine::Utils::ValidationLayers::enabled()
{
    return debugging;
}

bool Engine::Utils::ValidationLayers::checkSupport()
{
    uint32_t layersCount;
    vkEnumerateInstanceLayerProperties(&layersCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layersCount);
    vkEnumerateInstanceLayerProperties(&layersCount, availableLayers.data());

    for(const char* layerName : validationLayers)
    {
        bool layerFound = false;

        for(const auto& layerProperties : availableLayers)
        {
            if(strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if(!layerFound)
            return false;
    }

    return true;
}
