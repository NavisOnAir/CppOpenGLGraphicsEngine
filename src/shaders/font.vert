#version 330 core
layout (location = 0) in vec4 v_vertex; // <vec2 pos, vec2 tex>
out vec2 v_tex_coords;

uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection * vec4(v_vertex.xy, 1.0, 1.0);
    v_tex_coords = v_vertex.zw;
}  