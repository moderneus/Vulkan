#pragma once

#include <vector>

const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

bool check_validation_layers_support();
