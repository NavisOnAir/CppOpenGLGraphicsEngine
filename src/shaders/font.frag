#version 330 core
in vec2 v_tex_coords;
out vec4 f_color;

uniform sampler2D u_text;
uniform vec3 u_text_color;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_text, v_tex_coords).r);
	f_color = vec4(u_text_color, 1.0) * sampled;
}