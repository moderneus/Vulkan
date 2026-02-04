#ifndef MOD_VALIDATION_LAYERS_HPP
#define MOD_VALIDATION_LAYERS_HPP

#include <vector>

const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

bool check_validation_layers_support();

#endif
