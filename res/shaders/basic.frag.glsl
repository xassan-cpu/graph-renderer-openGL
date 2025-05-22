#version 330 core
in vec3 vPos;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vPos.x * 0.5 + 0.5, vPos.y * 0.5 + 0.5, 0.0, 1.0);
    //FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
