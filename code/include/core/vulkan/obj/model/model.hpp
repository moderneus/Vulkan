#ifndef MOD_MODEL_HPP
#define MOD_MODEL_HPP

#include "core/vulkan/obj/buffer/vertex.hpp"
#include "core/vulkan/obj/buffer/vertex_buffer.hpp"
#include "core/vulkan/obj/buffer/index_buffer.hpp"

#include <vector>
#include <string>

struct model {
	vertex_buffer vbuf;
	index_buffer ibuf;
};

void model_load(model *mod, const std::string &path);

#endif
