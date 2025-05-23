#version 330 core
in vec3 worldPos;
out vec4 FragColor;

void main()
{
    FragColor = vec4(worldPos.x * 0.5 + 0.5, worldPos.y * 0.5 + 0.5, 0.0, 1.0);
}
