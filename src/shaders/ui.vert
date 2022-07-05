#version 330 core

layout(location = 0) in vec2 a_position;

out vec4 v_color;

uniform vec4 u_color;
uniform mat4 u_projection;
uniform vec2 u_position;

void main()
{
    gl_Position = u_projection * vec4(a_position.x + u_position.x, a_position.y + u_position.y, 0.2f, 1.0f);
    v_color = u_color;
}   