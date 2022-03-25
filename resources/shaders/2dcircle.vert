#version 330 core

out vec2 position;

uniform vec3 aPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(0.0,0.0,0.0, 1.0);
    position = gl_Position.xy;
}