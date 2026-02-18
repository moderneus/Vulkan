#include "util/debug/val_layers.hpp"

#include <vulkan/vulkan.h>

#include <cstring>

bool val_layers_check_supp()
{
	uint32_t layer_cnt;
	vkEnumerateInstanceLayerProperties(&layer_cnt, nullptr);

	std::vector<VkLayerProperties> layers(layer_cnt);
	vkEnumerateInstanceLayerProperties(&layer_cnt, layers.data());

	for(const char *layer_name : val_layers) {
		bool found = false;

		for(const auto& layer_props : layers) {
			if (strcmp(layer_name, layer_props.layerName) == 0) {
				found = true;
				break;
			}
		}

		if (!found) {
			return false;
		}
	}
	return true;
}
