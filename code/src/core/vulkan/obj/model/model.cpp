#include "core/vulkan/obj/model/model.hpp"
#include "util/debug/log.hpp"

#define TINYOBJLOADER_IMPLEMENTATION

#include "tiny_obj_loader.h"

#include <unordered_map>
#include <cstdint>

void model_load(model *mod, const std::string &path) 
{
	log_info("Loading the Model by Path: ", path);

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) 
		log_error("Failed to Load the Model by Path: ", path + ". Error: " + err);

	std::unordered_map<vertex, uint32_t> unique_verts = {};

	for(const auto &shape : shapes) {
		for(const auto &idx : shape.mesh.indices) {
			vertex vert = {};

			vert.pos = {
				attrib.vertices[3 * idx.vertex_index + 0],
				attrib.vertices[3 * idx.vertex_index + 1],
				attrib.vertices[3 * idx.vertex_index + 2]
			};

			vert.tex = {
				attrib.texcoords[2 * idx.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * idx.texcoord_index + 1]
			};

			vert.col = {1.0f, 1.0f, 1.0f};

			if (unique_verts.count(vert) == 0) {
				unique_verts[vert] = static_cast<uint32_t>(mod->vbuf.data.size());
				mod->vbuf.data.push_back(vert);
			}

			mod->ibuf.data.push_back(unique_verts[vert]);
		}
	}

	log_info("The Model was Loaded by Path: ", path);
}
