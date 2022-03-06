#version 330 core
out vec4 FragColor;

uniform float uColor;

void main()
{
    FragColor = vec4(1.0f, uColor, 0.5f, 1.0f);
}