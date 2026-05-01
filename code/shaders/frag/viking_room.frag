#version 460

layout(binding = 1) uniform sampler2D tex_samp;

layout(location = 0) in vec3 frag_color;
layout(location = 1) in vec2 frag_tex_coord;

layout(location = 0) out vec4 out_color;

void main() 
{
	out_color = texture(tex_samp, frag_tex_coord);
}
