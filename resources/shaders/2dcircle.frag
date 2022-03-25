#version 330 core
in vec2 position;
out vec4 FragColor;

uniform float radius;

void main()
{
    FragColor = vec4(1.0f, gl_FragCoord.x, 0.5f, 1.0f);
}