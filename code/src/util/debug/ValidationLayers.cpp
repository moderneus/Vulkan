#include "util/debug/ValidationLayers.hpp"

#include <vulkan/vulkan.h>

#include <cstring>

bool check_validation_layers_support() 
{
	uint32_t layer_count;
	vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

	std::vector<VkLayerProperties> layers(layer_count);
	vkEnumerateInstanceLayerProperties(&layer_count, layers.data());

	for(const char* layer_name : validationLayers) {
		bool layerFound = false;

		for(const auto& layer_props: layers) {
			if (strcmp(layer_name, layer_props.layerName) == 0) {
				layerFound = true;
				break;
			}
		}
		if (!layerFound) {
			return false;
		}
	}
	return true;
}
