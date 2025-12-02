#pragma once

#include <vector>

namespace Engine
{
    namespace Utils
    {
        const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

        bool checkValidationLayerSupport();
    }
}